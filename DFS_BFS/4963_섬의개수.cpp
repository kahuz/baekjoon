//단순 미로찾기 문제
//BFS 연습용으로 풀이하자
#include <iostream>	//io
#include <queue>	//queue
#include <cstring>	//memset

using namespace std;

//해당 값이 땅인지 바다인지 구별하기 위한 상수값 정의
#define LAND	1
#define SEA		0

//지도 가로 세로 변수 선언 및 초기화
int W = 0, H = 0;

//지도배열 선언 및 초기화
int map[50][50] = { 0 };
//방문배열 선언 및 초기화
int check[50][50] = { 0 };

//다음 탐색을 위한 8방위 배열 선언 및 초기화
int dx[8] = { -1,0,1,1,1,0,-1,-1 };
int dy[8] = { -1,-1,-1,0,1,1,1,0 };
//bfs탐색을 위한 큐 선언
queue<pair<int, int>> bfs_q;

//param start_x, start_y : 탐색을 시작할 위치
void find_island(int start_x, int start_y)
{
	//땅으로 판별된 탐색 시작 위치를 큐에 삽입
	bfs_q.push(make_pair(start_x, start_y));
	//해당 위치에 방문했음을 표시
	check[start_y][start_x] = true;

	//큐의 노드가 모두 탐색될때까지 루프
	while (!bfs_q.empty())
	{
		//현재 탐색 위치를 받아온다
		int x = bfs_q.front().first;
		int y = bfs_q.front().second;
		//사용한 노드는 반납
		bfs_q.pop();

		//현재 탐색 위치에 대해 8방위 탐색을 시작
		for (int i = 0; i < 8; i++)
		{
			//다음 탐색 위치를 받아온다
			int xn = x + dx[i];
			int yn = y + dy[i];

			//다음 탐색 위치가 지도를 벗어나면 스킵
			if (xn < 0 || xn >= W || yn < 0 || yn >= H)	continue;

			//다음 탐색 위치가 땅이고, 아직 방문하지 않았다면
			if (map[yn][xn] == LAND && check[yn][xn] == false)
			{
				//다음 탐색을 위해 탐색 위치를 삽입
				bfs_q.push(make_pair(xn, yn));
				//이미 방문하였음을 check 배열에 저장
				check[yn][xn] = true;
			}
		}
	}
}
int main(void)
{
	while (true)
	{
		int res = 0;
		//지도의 가로 세로 크기를 받아온다
		cin >> W >> H;
		//만약 지도의 크기가 0 이라면 더이상 입력이 없으므로 break;
		if (W == 0 && H == 0)
			break;

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				cin >> map[i][j];


		//지도에서 0,0 기준으로 땅이 있는 곳을 모두 순회
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				//현재 인덱스가 지도상 땅이며, 아직 방문하지 않은 ( 이전 탐색과 연결되지 않은 땅 ) 땅이라면
				if (map[i][j] == 1 && check[i][j] == false)
				{
					//섬을 발견했으므로 결과값 + 1
					res++;
					//섬을 발견한 위치를 매개변수로 find_island 호출
					//섬의 위치를 시작으로 연결된 모든 땅들을 방문하여 중복 입장이 되지 않도록 한다
					find_island(j, i);
				}
			}

		//찾은 섬의 개수 출력
		cout << res << endl;
		//다음 지도에서 방문여부를 표시하기 위해 check 배열 초기화
		memset(check, 0, sizeof(check));

	}

	return 0;
}
