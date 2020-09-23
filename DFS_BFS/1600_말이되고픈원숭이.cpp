//
// 체스판 나이트와 같은 이동방식을 k번 할 수 있고, 그 외에는 인접한 칸으로만 이동 가능할때
// 격자판의 맨 왼쪽 위에서 맨 오른쪽 아래로 가는 최소 동작의 횟수를 구하시오
// 단, 격자판은 빈칸(0)과 장애물(1)로 구성되어있고, 장애물에는 갈 수 없다
//
// 탐색의 최소거리를 구하는것이므로 BFS로 접근, 이동가능 방법을 상하좌우와
// 나이트의 이동방법 8개를 섞어서 이동하게 해주며, 나이트의 이동방법은 k번 모두 소진시 사용않도록해서 탐색
//
// **나이트의 이동에 대한 방문처리를 별개로 처리할 수 있게 하여야한다
// **즉, 탐색 위치에 대해 n번째 나이트의 이동으로 접근한 경우와 그 외의 경우를 별개로 처리해야함
// **예를 들어 아래와 같은 반례가 있을 수 있음
//		1
//		5 5
//		0 0 0 0 0
//		0 0 0 0 0
//		0 0 0 0 0
//		0 0 0 1 1
//		0 0 0 1 0  
//
#include <iostream>
#include <queue>

using namespace std;

//보드판 상태
int board[200][200] = { 0 };
//중복방문 상태, 31은 나이트로 이동 가능한 횟수에 대한 의미를 내포
int check[200][200][31] = { 0 };
//상우하좌, 나이트 이동방법 시계방향순
int dx[12] = { 0,1,0,-1, 1,2,2,1,-1,-2,-2,-1 };
int dy[12] = { -1,0,1,0, -2,-1,1,2,2,1,-1,-2 };
//현재위치 x,y와 나이트이동횟수 k, 경로 이동횟수로 구성된 bfs_q
queue<pair<pair<int,int>,pair<int,int>>> bfs_q;
//입력 및 출력에 대한 변수
int K = 0, H = 0, W = 0, res = 1e9;

void bfs()
{
	//시작 위치에 대한 q 변수 삽입
	bfs_q.push(make_pair(make_pair(0,0), make_pair(0,0)));
	//방문처리
	check[0][0][0] = true;

	//bfs_q가 모두 소진될때까지
	while (!bfs_q.empty())
	{
		//탐색 위치에 대한 정보를 가져온다
		int x = bfs_q.front().first.first;
		int y = bfs_q.front().first.second;
		int k = bfs_q.front().second.first;
		int cnt = bfs_q.front().second.second;

		bfs_q.pop();
		//목표에 도달했으면 출력하고 return
		if (x == W - 1 && y == H - 1)
		{
			cout << cnt << endl;
			return;
		}
		//다음 탐색 위치 확인
		for (int i = 0; i < 12; i++)
		{
			int xn = x + dx[i];
			int yn = y + dy[i];

			if (xn < 0 || xn >= W || yn < 0 || yn >= H)	continue;
			//인접지역에 대한 처리
			if (i < 4)
			{
				if (board[yn][xn] == 0 && check[yn][xn][k] == false)
				{
					check[yn][xn][k] = true;
					bfs_q.push(make_pair(make_pair(xn, yn), make_pair(k, cnt + 1)));
				}
			}
			//나이트 이동에 대한 처리
			else if (i > 3 && k < K)
			{
				if (board[yn][xn] == 0 && check[yn][xn][k + 1] == false)
				{
					check[yn][xn][k + 1] = true;
					bfs_q.push(make_pair(make_pair(xn, yn), make_pair(k + 1, cnt + 1)));
				}
			}
		}
	}
	//목표에 도달 못했다면 -1 출력
	cout << -1 << endl;
}
int main(void)
{
	//나이트 이동 횟수 및 보드 크기를 받아온다
	cin >> K >> W >> H;
	//보드 상태를 입력받는다
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++)
			cin >> board[y][x];
	//탐색시작
	bfs();

	return 0;
}