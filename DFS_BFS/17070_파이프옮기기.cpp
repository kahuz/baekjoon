//
// 조건
// - NxN 크기의 집이 있으며 각 칸은 (r,c)로 나타낼 수 있다
// - 행과 열은 1번부터 시작하며, 각 칸은 빈칸(0)이거나 벽(1)이다
// - 집 수리를 위해 파이프 하나를 옮기려하고 파이프는 2개의 연속된 칸을 차지하는 크기이다
// - 파이프는 3가지의 방향으로 구성된다
// - 파이프는 빈칸으로만 이동 가능하다
// - 파이프는 밀면서 회전이 가능하고 회전은 45도 회전만 가능하다
// - 미는 방향은 오른쪽, 아래, 또는 오른쪽 대각선 방향(→, ↘, ↓)이어야한다.
// - *기존 파이프가 가로로 놓여진 경우 오른쪽, 오른쪽아래 대각선
// - *세로로 놓여진 경우 아래, 오른쪽아래 대각선
// - *대각선은 오른쪽,아래, 오른쪽아래 대각선 으로 가능
// - ***첫 파이프는 (0,0)과 (0,1)를 차지하고 있고 방향은 가로이다
//   즉, 항상 시작은 (0,1)에서 시작하는 것
//
// 입력
// - 첫째줄 : 집크기 N ( 3 <= N <= 16 )
// - 2~N+1 : 집 상태 ( 0은 빈칸, 1은 벽 )
#include<iostream>
#include<queue>

#define DEF_R 0
#define DEF_D 1
#define DEF_RD 2
using namespace std;

int map[16][16];
//x,y,dir
queue<pair<pair<int, int>, int > > bfs_q;

int dx[] = { 1, 0, 1 };
int dy[] = { 0, 1, 1 };

int N = 0, res = 0;

void bfs()
{

	bfs_q.push(make_pair(make_pair(1, 0), 0));

	while (!bfs_q.empty())
	{
		int x = bfs_q.front().first.first;
		int y = bfs_q.front().first.second;
		int dir = bfs_q.front().second;

		bfs_q.pop();

		if (x == N - 1 && y == N - 1)
		{
			res++;
			continue;
		}

		switch (dir)
		{
			int xn, yn;
		case DEF_R:

			xn = x + dx[DEF_R];
			yn = y + dy[DEF_R];
			if (xn >= 0 && yn >= 0 && xn < N && yn < N)
			{
				if (map[yn][xn] == 0)
				{
					bfs_q.push(make_pair(make_pair(xn, yn), DEF_R));
				}
			}

			xn = x + dx[DEF_RD];
			yn = y + dy[DEF_RD];
			if (xn >= 0 && yn >= 0 && xn < N && yn < N)
			{
				if (map[yn][xn] == 0 && map[y][x + 1] == 0 && map[y + 1][x] == 0)
				{
					bfs_q.push(make_pair(make_pair(xn, yn), DEF_RD));
				}
			}
			break;
		case DEF_D:

			xn = x + dx[DEF_D];
			yn = y + dy[DEF_D];
			if (xn >= 0 && yn >= 0 && xn < N && yn < N)
			{
				if (map[yn][xn] == 0)
				{
					bfs_q.push(make_pair(make_pair(xn, yn), DEF_D));
				}
			}

			xn = x + dx[DEF_RD];
			yn = y + dy[DEF_RD];
			if (xn >= 0 && yn >= 0 && xn < N && yn < N)
			{
				if (map[yn][xn] == 0 && map[y][x + 1] == 0 && map[y + 1][x] == 0)
				{
					bfs_q.push(make_pair(make_pair(xn, yn), DEF_RD));
				}
			}
			break;

		case DEF_RD:

			xn = x + dx[DEF_RD];
			yn = y + dy[DEF_RD];
			if (xn >= 0 && yn >= 0 && xn < N && yn < N)
			{
				if (map[yn][xn] == 0 && map[y][x + 1] == 0 && map[y + 1][x] == 0)
				{
					bfs_q.push(make_pair(make_pair(xn, yn), DEF_RD));
				}
			}

			xn = x + dx[DEF_R];
			yn = y + dy[DEF_R];

			if (xn >= 0 && yn >= 0 && xn < N && yn < N)
			{
				if (map[yn][xn] == 0)
				{
					bfs_q.push(make_pair(make_pair(xn, yn), DEF_R));
				}
			}

			xn = x + dx[DEF_D];
			yn = y + dy[DEF_D];

			if (xn >= 0 && yn >= 0 && xn < N && yn < N)
			{
				if (map[yn][xn] == 0)
				{
					bfs_q.push(make_pair(make_pair(xn, yn), DEF_D));
				}
			}
			break;
		}
	}
}


int main(void)
{

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}

	bfs();
	cout << res << endl;
	return 0;
}
