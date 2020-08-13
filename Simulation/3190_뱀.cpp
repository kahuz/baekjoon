//
// 3190 뱀
//
// 조건
// - NxN 정사각보드에 사과들이 놓여있다.
// - 보드의 상하좌우 끝에는 벽이 있으며, 게임 시작시 길이 1의 뱀이 맨좌측 위에 위치한다.
// - 뱀은 처음에 오른쪽으로 향하며 매 초마다 이동을할때 아래 규칙을 따른다.
//	-> 먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
//	-> 만약 이동한 칸에 사과가 있다면, 그 칸의 사과가 없어지고 꼬리는 움직이지 않는다.
//	-> 만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다. 즉, 몸길이는 변하지않는다.
// - 뱀이 움직이다가 벽 또는 자기자신의 몸과 부딪치면 게임이 끝난다.
// - 사과의 위치와 뱀의 이동경로가 주어질때 이 게임이 몇 초에 끝나는지 계산하라.
//
// 입력
// - 첫째줄 : 보드의 크기 N ( 2 <= N <= 100 ) 이 주어짐
// - 둘째줄 : 사과의 개수 K ( 0 <= K <= 100 ) 이 주어짐
// - 3~K+2줄 : 사과의 위치가 주어짐. 첫 번째 정수는 행, 두번째 정수는 열의 위치를 의미.
//			-> 사과의 위치는 모두 다르며, 맨 위 맨 좌측 (1행1열)에는 사과가 없다.
// - K+3줄 : 뱀의 방향 변환 횟수 L ( 1 <= L <= 100 ) 이 주어짐
// - 이후 L줄 : 뱀의 방향 정보가 주어지는데, 정수 X와 문자 C로 이루어져 있다.
//			-> 게임 시작 시간으로부터 x초가 끝난 뒤에 왼쪽(C가 'L') 또는 오른쪽(C가 'D')로 90도 방향 회전을 시킨다
//			-> X는 10,000 이하의 양의 정수이며, 방향 전환 정보는 X가 증가하는 순으로 주어진다.
//
// 접근
// - 뱀의 움직임 방향 ( 초기 오른쪽 ) 을 기준으로 현재 시간값이 입력으로 주어진 시간에 도달하기 전까지 움직여준다
// - 움직일 다음 방향이 빈 공간이라면 다음 위치를 push하고 다음 위치에 도달했을때 꼬리 정보를 pop해준다
// - 움직일 다음 방향이 사과라면 사과를 먹고(사과값 2를 0으로 변환) 다음 위치로 이동 ( 꼬리 pop을 하지 않는다 )
// - 다음 위치가 벽이거나 몸통이 존재하는 ( deque에 위치정보가 포함되어있다면 ) 곳이라면 현재 시간을 반환하고 종료
#include <iostream>
#include <deque>
using namespace std;

//지도 정보를 위한 상수 정의
#define	MAP_EMPTY		0
#define MAP_WALL		1
#define MAP_APPLE		2
//뱀의 방향 전환을 위한 상수 정의
#define SNAKE_UP		0
#define SNAKE_DOWN		1
#define SNAKE_LEFT		2
#define SNAKE_RIGHT		3
//벽을 포함한 지도 배열 선언 및 초기화, row, colum의 시작과 끝에 벽을 위한 요소(1)를 추가하여 102 x 102
int board[102][102] = { 0 };
//뱀의 몸통 위치를 저장하는 디큐 선언
deque<pair<int, int>> snake_pos;
//지도의 크기 및 사과 정보와 뱀 정보 변수 선언 및 초기화
int N = 0, K = 0, L;
//뱀의 방향을 저장할 변수 선언 및 초기화
int s_dir = 3;
//결과변수 선언 및 초기화
int res_time = 0;
//param x,y : 뱀의 충돌 검사를 위한 위치
//입력 변수에 대해 뱀의 몸통과 겹치는지 확인하는 함수
bool check_crash(int x, int y)
{
	deque<pair<int, int>>::iterator dq_iter;
	//x,y좌표가 depue의 요소와 일치하는지 검사, 일치하면 충돌발생(true)
	for (dq_iter = snake_pos.begin(); dq_iter != snake_pos.end(); ++dq_iter)
	{
		if (dq_iter->first == x && dq_iter->second == y)
			return true;
	}

	return false;
}
//param next_dir : 다음 방향전환 값 D, L
//뱀의 방향 전환을 위한 함수
void snake_dir(char next_dir)
{
	switch (s_dir)
	{
	case SNAKE_UP:
		if (next_dir == 'D')
			s_dir = SNAKE_RIGHT;
		else if (next_dir == 'L')
			s_dir = SNAKE_LEFT;
		break;
	case SNAKE_DOWN:
		if (next_dir == 'D')
			s_dir = SNAKE_LEFT;
		else if (next_dir == 'L')
			s_dir = SNAKE_RIGHT;
		break;
	case SNAKE_LEFT:
		if (next_dir == 'D')
			s_dir = SNAKE_UP;
		else if (next_dir == 'L')
			s_dir = SNAKE_DOWN;
		break;
	case SNAKE_RIGHT:
		if (next_dir == 'D')
			s_dir = SNAKE_DOWN;
		else if (next_dir == 'L')
			s_dir = SNAKE_UP;
		break;
	}
}
//param time : 다음 방향 전환까지의 시간
//param x,y : 현재 뱀이 움직인 위치
//param dir : 현재 뱀의 진행 방향
//param is_stretch : 사과를 먹고 몸통을 늘일지 아닐지를 결정할 변수
bool play_game(int time, int x, int y, int dir, bool is_stretch)
{
	int xn = 0, yn = 0;
	//움직인 위치가 빈공간이므로, 꼬리를 줄여준다
	if (!is_stretch)
	{
		snake_pos.pop_front();
	}
	//움직인 시간이 time값과 같으면 현재 움직임 종료
	if (res_time == time)
	{
		return true;
	}
	//방향에 따른 다음 위치값 설정
	switch (dir)
	{
	case SNAKE_UP:
		xn = x;
		yn = y - 1;
		break;
	case SNAKE_DOWN:
		xn = x;
		yn = y + 1;
		break;
	case SNAKE_LEFT:
		xn = x - 1;
		yn = y;
		break;
	case SNAKE_RIGHT:
		xn = x + 1;
		yn = y;
		break;
	}
	//다음 진행에 대한 시간값 증가
	res_time++;
	//다음 위치가 벽이거나 몸통과 충돌했을 경우 false 반환
	if (board[yn][xn] == MAP_WALL || check_crash(xn, yn))
	{
		return false;
	}
	//다음 위치로 진행이 가능할 경우 위치값을 deque에 저장
	snake_pos.push_back(make_pair(xn, yn));
	//다음 위치에 사과가 있을 경우
	if (board[yn][xn] == MAP_APPLE)
	{
		//사과를 먹었으므로 MAP_EMPTY 변환
		board[yn][xn] = MAP_EMPTY;
		//몸통 길이를 늘이기 위해 마지막 변수를 true로 전달
		return play_game(time, xn, yn, dir, true);
	}
	if (board[yn][xn] == MAP_EMPTY)
	{
		//다음 공간이 빈 공간이므로 꼬리를 줄이기 위해 마지막 변수를 false로 전달
		return play_game(time, xn, yn, dir, false);
	}

}

int main(void)
{
	//맵 크기 변수 입력
	cin >> N;
	//맵 정보 입력
	for (int y = 0; y <= N + 1; y++)
	{
		for (int x = 0; x <= N + 1; x++)
		{
			if (y == 0 || x == 0 || x == N + 1 || y == N + 1)
				board[y][x] = MAP_WALL;
		}
	}
	//사과 갯수를 입력 받아온다
	cin >> K;
	//입력받은 사과정보를 반영
	for (int i = 0; i < K; i++)
	{
		int k_y, k_x;
		cin >> k_y >> k_x;
		board[k_y][k_x] = MAP_APPLE;
	}
	//뱀의 움직임 케이스 입력
	cin >> L;
	//뱀 시작 위치 입력
	snake_pos.push_back(make_pair(1, 1));
	//움직임 케이스만큼 loop
	for (int j = 0; j < L; j++)
	{
		//움직임 반영 시간값
		int l_time;
		//움직임 값
		char l_dir;
		//움직임을 반영하기까지의 시간과 움직임에 대한 정보를 입력받는다
		cin >> l_time >> l_dir;
		//뱀 움직임 함수 시작
		if (!play_game(l_time, snake_pos.back().first, snake_pos.back().second, s_dir, true))
		{
			//벽이나 몸통에 충돌했을 시 종료
			cout << res_time << endl;
			return 0;
		}
		//움직임 종료 후 다음 움직임 방향을 정하기 위한 함수 호출
		snake_dir(l_dir);
	}
	//모든 테스트 케이스를 돌린 후 충돌이 일어나지 않았다면 마지막 진행 방향으로 게임을 진행
	//time값은 테스트 케이스의 최대 움직임 시간이 10,000인 것과 뱀의 움직임 배열 크기가 100을 고려하여 10,100으로 전달
	play_game(10100, snake_pos.back().first, snake_pos.back().second, s_dir, true);

	cout << res_time << endl;

	return 0;
}
