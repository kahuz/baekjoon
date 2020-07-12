#include <iostream>	// io
#include <queue>	// queue
#include <vector>	// vector

using namespace std;

//영역이 그려질 종이에 대한 배열 선언 및 초기화
int paper[100][100] = { 0 };

//영역에 대한 세로(N) 가로(M) 그리고 그려진 영역의 개수(K)에 대한 선언 및 초기화
int N = 0, M = 0, K = 0;

//영역 탐색을 위한 방위 배열 선언 및 초기화
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

//bfs 탐색을 위한 큐 선언
queue<pair<int, int>> bfs_q;
//bfs 탐색 결과를 저장할 벡터 선언
vector<int> res;

//param x, y : 탐색 시작 위치
int bfs(int x, int y)
{
	//bfs 호출 전 빈 영역에 대해 호출하였으므로
	//기본 크기는 1로 할당하여 준다
	int area_size = 1;
	//탐색 시작 위치를 큐에 삽입
	bfs_q.push(make_pair(x, y));
	//탐색 시작 위치에 대해 paper 배열에 표시
	paper[y][x] = 1;

	while (!bfs_q.empty())
	{
		//탐색할 위치의 x,y좌표를 가져온다
		int x = bfs_q.front().first;
		int y = bfs_q.front().second;
		//사용된 노드는 큐에서 반납
		bfs_q.pop();
		//영역 크기를 탐색하기 위한 상 우 하 좌 탐색 시작
		for (int i = 0; i < 4; i++)
		{
			int xn = x + dx[i];
			int yn = y + dy[i];

			//다음 탐색 위치인 xn과 yn이 탐색 범위를 벗어날 경우 스킵
			if (xn < 0 || xn >= M || yn < 0 || yn >= N)	continue;

			if (paper[yn][xn] == 0)
			{
				bfs_q.push(make_pair(xn, yn));
				paper[yn][xn] = 1;
				area_size++;
			}
		}
	}
	return area_size;

}

int main(void)
{
	//영역에 대한 세로(N) 가로(M) 영역의 개수(K)를 입력받는다
	cin >> N >> M >> K;

	//영역을 그리기 위한 입력 루틴
	//영역은 배열상 표시하기 쉽게 예제에 반전된 이미지로 저장하여 처리
	//예제는 y축이 수학에서 통상으로 사용하는 좌표체계이고
	//본 코드에서는 배열에서 사용되는 좌표체계이다. 백준 예문을 확인하고 코드를 확인할 것
	for (int i = 0; i < K; i++)
	{
		int tmp_x1 = 0, tmp_x2 = 0;
		int tmp_y1 = 0, tmp_y2 = 0;

		cin >> tmp_x1 >> tmp_y1 >> tmp_x2 >> tmp_y2;

		for (int j = tmp_y1; j < tmp_y2; j++)
		{
			for (int k = tmp_x1; k < tmp_x2; k++)
			{
				paper[j][k] = 1;
			}
		}

	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			//paper[i][j] == false라면 아직 탐색하지 않은 영역이므로
			//( j , i ) 를 시작으로 bfs 탐색을 하여 영역의 크기를 구해준 뒤
			//res 벡터에 결과값을 넣어준다
			if (paper[i][j] == 0)
				res.push_back(bfs(j, i));
		}
	}

	int buble_max = res.size();
	//버블 정렬로 결과값을 오름차순 정렬해준다
	for (int i = 0; i < buble_max; i++)
		for (int j = 0; j < (buble_max - 1) - i; j++)
		{
			if (res[j] > res[j + 1])
			{
				int tmp = res[j];
				res[j] = res[j + 1];
				res[j + 1] = tmp;
			}
		}
	//res에 저장된 영역의 개수 출력
	cout << buble_max << endl;
	//영역에 대한 크기를 오름차순으로 출력
	for (int i = 0; i < buble_max; i++)
		cout << res[i] << " ";

	cout << endl;
	return 0;
}