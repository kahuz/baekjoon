// 16234 인구이동
// 
// 조건 - NxN크기의 땅에 각 나라(x,y)가 있으며, 각 나라는 A[y][x] 명이 살고 있다
// 인접한 나라 사이에는 국경선이 존재한다
// 인구이동은 아래와 같이 진행되며 더 이상 인구이동이 없을때까지 지속된다
// - 국경선을 공유하는 '두 나라의 인구차가 L <= 인구 차이값 <=R '일때 국경선을 하루동안 연다
// - 위 조건으로 '하루동안 모든 국경선을 연 다음' 인구이동이 시작된다
// - 국경선이 열려 인접한 나라가 이동할 수 있을때 그 나라들은 하루동안 연합이라 한다
// - 연합을 이루는 각 칸의 인구수는 (연합의 인구수) / (연합 나라 수 ) 가 된다. '소수점은 버림'
// - 연합을 해체하고 모든 국경선을 닫는다
// - 위 조건은 위에 명시했듯 인구이동이 없을때까지 지속
// 각 나라의 인구수가 주어졌을때 인구 이동이 몇번 발생하는지 구하는 프로그램을 작성하라
//
// 입력
// - 첫째줄 : 지도크기 N(1<= N <= 50)과 인구 조건값 L, R( 1<= L <= R <= 100 )이 주어짐
// - 2~N-1줄 : 각 나라의 인구수(A[y][x])가 주어짐 ( 0 <= A[y][x] <= 100)
// - * 인구이동 횟수 <= 2000
//
// 접근법
// 1. 하나의 나라를 시작점으로 지정하고 인접한 나라의 인구차를 확인하여 
//   국경선을 열 수 있는 상태인지 확인한다
// 2. BFS 탐색을 이용하여 이동할 수 있는 나라에 대해 접근(push & check)하고 1번으로 돌아간다
// 3. 1-2를 반복하다 더이상 1->2로 갈 수 없는 상황일때 check된 지역들에 대해 인구값을 새로 지정
// 4. 다시 1-2-3 을 반복하며 더이상 반복할 수 없을때 인구이동이 끝난걸로 간주한다.

#include <iostream>	//io
#include <queue>	//queue
#include <cstdlib>	//int abs()
#include <cstring>	//memset

using namespace std;
//인구수가 기록될 지도배열 선언 및 초기화
int map[50][50] = { 0 };
//인구이동 발생지역 확인을 위한 배열 선언 및 초기화
int check[50][50] = { 0 };
//탐색을 위한 방위배열 선언 및 초기화
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

//인구이동 발생지역을 탐색할 큐 선언
queue<pair<int, int>> bfs_q;

//초기 입력 값 선언 및 초기화
int N = 0, L = 0, R = 0;
//결과를 저장할 변수 선언 및 초기화
int res_move = 0;

//탐색지점 x,y에 대해 국경이 열릴 수 있는지 확인
bool get_ismove(int x, int y)
{
	bool is_move = false;

	for (int i = 0; i < 4; i++)
	{
		int xn = x + dx[i];
		int yn = y + dy[i];

		if (xn < 0 || xn >= N || yn < 0 || yn >= N)	continue;

		int diff = abs(map[y][x] - map[yn][xn]);

		if (L <= diff && diff <= R)
		{
			//인구이동이 가능하므로 true
			is_move = true;

		}
	}
	return is_move;
}
void bfs(int start_x, int start_y)
{
	//인구 재설정을 위한 큐 선언
	queue<pair<int, int>> reset_q;
	//인구 재설정을 위한 변수 선언
	int sum_people = map[start_y][start_x];
	int country_cnt = 1;
	//탐색지역에 대해 방문표시 및 탐색시작을 위한 좌표값 삽입
	check[start_y][start_x] = true;
	bfs_q.push(make_pair(start_x, start_y));
	reset_q.push(make_pair(start_x, start_y));

	//탐색지역이 없을때까지 루프
	while (!bfs_q.empty())
	{
		//탐색지역 x,y값을 가져옴
		int x = bfs_q.front().first;
		int y = bfs_q.front().second;
		//가져온 노드는 반납
		bfs_q.pop();
		//4방위에 대해 인구이동이 가능한지 확인
		for (int i = 0; i < 4; i++)
		{
			int xn = x + dx[i];
			int yn = y + dy[i];

			if (xn < 0 || xn >= N || yn < 0 || yn >= N)	continue;
			//다음 지역에 대해 인구이동 가능 조건인지 확인
			int diff = abs(map[y][x] - map[yn][xn]);
			//인구이동 조건이라면
			if (L <= diff && diff <= R && check[yn][xn] == false)
			{
				//중복 탐색을 하지 않도록 check배열 true
				check[yn][xn] = true;
				bfs_q.push(make_pair(xn, yn));
				//연합에 대한 정보 입력
				reset_q.push(make_pair(xn, yn));
				sum_people += map[yn][xn];
				country_cnt++;

			}
		}
	}
	//연합 결과 값을 산출
	int reset_value = sum_people / country_cnt;
	//연합 결과를 지도에 반영
	while (!reset_q.empty())
	{
		int x = reset_q.front().first;
		int y = reset_q.front().second;
		reset_q.pop();

		map[y][x] = reset_value;
	}
}

void set_start_point()
{
	//인구이동 발생 여부에 대한 bool 변수 선언
	bool is_continue = true;
	//인구이동이 발생하지 않을때까지 루프
	while (is_continue)
	{
		is_continue = false;
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				// 아직 방문하지 않았고 다음 지역으로 이동 가능할때
				if (!check[y][x] && get_ismove(x, y))
				{
					//인구이동이 발생했으므로 다음 탐색을 위해 true
					is_continue = true;
					bfs(x, y);
				}
			}
		}
		//인구이동이 발생했다면, check배열 초기화를 통해 재탐색 여부 확인 및
		//모든 지역에 대한 인구이동 여부를 확인했으므로 res_move ++
		if (is_continue)
		{
			memset(check, 0, sizeof(check));
			res_move++;
		}
	}
}
int main(void)
{
	cin >> N >> L >> R;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];
		}
	}

	set_start_point();
	cout << res_move << endl;
	return 0;
}