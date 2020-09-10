// 09:05
// 조건
// - NxM지도가 존재한다, 지도의 오른쪽은 동쪽, 위쪽은 북쪽이다
// - 지도의 좌표는 (r,c)로 나타내며, r은 북에서 떨어진, c는 서에서 떨어진 칸의 개수이다
// - 주사위는 지도 위의 윗면이 1이고 동쪽을 바라보는 방향이 3인 상태로 놓여있으며
//   놓여져있는 곳의 좌표는 (x,y)이다
// - *가장 처음에 주사위에는 모든 면이 0이 적혀 있다
// - 지도의 각 칸에는 정수가 하나씩 쓰여져있다. 주사위를 굴렸을 때 이동한 칸에 쓰여있는 수가 0 이면
//  주사위의 바닥면에 쓰여있는 수가 칸에 복사된다
// - 0이 아닌 경우에는 칸에 쓰여있는 칸에 쓰인 수가 주사위의 바닥에 복사되고 칸은 0이 된다
// - 주사위를 놓은 곳의 좌표와 이동시키는 명령어가 주어졌을때, 주사위가 이동햇을때마다 상단에 쓰여있는 값을 구하라
// - 주사위는 지도 바깥으로 이동시킬 수 없다. 이 경우 명령어를 무시 및 출력도 무시한다
//
// 입력
// - 첫째줄 : 세로 N 가로 M, 주사위 위치 x, y, 명령어 개수 8
// - 1~1+N : 지도 정보
// - 마지막 : 명령어 정보
//
//
#include <iostream>

using namespace std;

int map[20][20] = { 0 };
int oper[1000] = { 0 };
int dice[6] = { 0 };
int dx[5] = { 0,1,-1,0,0 };
int dy[5] = { 0,0,0,-1,1 };
int oper_n = 0;
int N = 0, M = 0;
int start_x = 0, start_y = 0;

void move_dice(int oper)
{
	int d1 = dice[0], d2 = dice[1], d3 = dice[2];
	int d4 = dice[3], d5 = dice[4], d6 = dice[5];

	switch (oper)
	{
	case 1:

		dice[0] = d4;
		dice[3] = d6;
		dice[5] = d3;
		dice[2] = d1;

		break;
	case 2:

		dice[3] = d1;
		dice[5] = d4;
		dice[2] = d6;
		dice[0] = d3;

		break;
	case 3:

		dice[0] = d5;
		dice[1] = d1;
		dice[5] = d2;
		dice[4] = d6;

		break;
	case 4:

		dice[4] = d1;
		dice[0] = d2;
		dice[1] = d6;
		dice[5] = d5;
		break;
	}
}
void play_game(int start_x, int start_y)
{
	int x = start_x;
	int y = start_y;

	for (int i = 0; i < oper_n; i++)
	{
		int xn = x + dx[oper[i]];
		int yn = y + dy[oper[i]];
		int op = oper[i];
		//지도 범위 넘어가면 명령을 하달하지 않고 무시할것
		if (xn < 0 || xn >= M || yn < 0 || yn >= N)	continue;
		//움직이는 위치(명령)에 따라 주사위 이동(회전)
		move_dice(op);

		//다음 위치 지도 값이 0이면 주사위의 밑면을 복사
		if (map[yn][xn] == 0) 
			map[yn][xn] = dice[5];
		else
		{
			dice[5] = map[yn][xn];
			map[yn][xn] = 0;
		}

		cout << dice[0] << endl;
		x = xn;
		y = yn;
	}
}

int main(void)
{

	cin >> N >> M >> start_y >> start_x >> oper_n;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
		}
	}

	for (int z = 0; z < oper_n; z++)
		cin >> oper[z];

	play_game(start_x, start_y);

	return 0;
}