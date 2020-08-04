#include <iostream>	//io
#include <queue>	//queue
#include <cstring>	//memset;
using namespace std;

//지도 배열 선언 및 초기화
int map[50][50] = { 0 };
//방문 확인 배열 선언 및 초기화
int check[50][50] = { 0 };

//bfs탐색을 위한 방위 배열 선언 및 초기화
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
//bfs탐색을 위한 큐 선언
queue<pair<int, int>> bfs_q;
//입력 테스트 케이스 변수 선언 및 초기화
int T = 0;
//테스트케이스별 지도 크기 M x N 변수와 배추의 위치 K 변수 선언 및 초기화
int N = 0, M = 0, K = 0;

//param start_x,start_y : bfs탐색 시작 위치
void bfs(int start_x, int start_y)
{
	//탐색한 지역에 대해 방문표시
	check[start_y][start_x] = 1;
	//탐색 시작 위치를 큐에 입력
	bfs_q.push(make_pair(start_x, start_y));
	//모든 탐색이 완료될때까지 while을 통해 탐색
	while (!bfs_q.empty())
	{
		//현재 탐색 위치 값을 가져온다
		int x = bfs_q.front().first;
		int y = bfs_q.front().second;
		//값을 가져온 노드는 반환
		bfs_q.pop();
		//4방위로 탐색하여 다음 탐색지역이 있는지 확인한다
		for (int i = 0; i < 4; i++)
		{
			//다음 탐색 위치를 가져온다
			int xn = x + dx[i];
			int yn = y + dy[i];
			//탐색 위치가 배열을 벗어나면 continue
			if (xn < 0 || xn >= M || yn < 0 || yn >= N)	continue;
			//다음 탐색 위치에 배추가 있고 아직 방문하지 않았다면
			if (map[yn][xn] == 1 && check[yn][xn] == false)
			{
				//방문을 위해 큐에 삽입 및 방문표시를 해준다
				bfs_q.push(make_pair(xn, yn));
				check[yn][xn] = true;
			}
		}
	}
}
//테스트 케이스별 모든 지도를 확인하고
//배추를 발견했을때 bfs탐색을 이용해 연결된 배추들을 모두 찾아준다
//연결된 배추는 모두 지렁이 하나로 오염(?)이 가능하므로, bfs탐색 하나당 지렁이 하나 배정
int solution()
{
	int warm = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			//배추가 있고 아직 방문을 하지 않았다면
			if (map[y][x] == 1 && check[y][x] == false)
			{
				//연결된 배추에 대해 방문표시를 위해 bfs탐색을 해주고
				bfs(x, y);
				//지렁이를 하나 살포
				warm++;
			}
		}
	}
	//최종 지렁이의 수를 반환
	return warm;
}

int main(void)
{
	cin >> T;

	while (T--)
	{
		cin >> M >> N >> K;
		//테스트 케이스별 방문배열과 지도배열을 초기화해준다
		memset(check, 0, sizeof(check));
		memset(map, 0, sizeof(map));
		//배추의 위치 입력값을 받아온다
		for (int i = 0; i < K; i++)
		{
			int x, y;
			cin >> x >> y;
			map[y][x] = 1;
		}
		//문제풀이 함수를 실행하고 지렁이의 수를 반환받는다
		cout << solution() << endl;

	}

	return 0;

}