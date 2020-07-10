#include <iostream>	//io
#include <queue>	//queue
#include <string>	//string
#include <tuple>	//tuple
using namespace std;

//도착위치 N,M을 위한 변수 선언 및 초기화
int N = 0, M = 0;
//경로가 그려질 지도 배열 선언 및 초기화
int map[100][100] = { 0 };
//이미 방문한 위치에 대해 중복 입장을 하지 않기 위한 배열 선언 및 초기화
bool check[100][100] = { 0 };
//bfs탐색을 위한 x,y,move 값을 가지는 큐 선언
queue<tuple<int, int, int>> bfs_q;

//경로 이동을 위한 방위행렬 선언 및 초기화 상우하좌 순.
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

//return : 목적지까지 움직인 횟수. 움직임은 현재 위치를 1로 기준으로 삼아 움직인다
int bfs()
{
	//bfs 탐색 시작 위치와 초기 이동횟수를 큐에 삽입
	//문제에서는 배열상 0,0을 시작 위치로 설정
	bfs_q.push(make_tuple(0, 0, 1));
	check[0][0] = true;

	while (!bfs_q.empty())
	{
		//현재 방문한 위치의 x,y값과 현재 위치까지 움직인 횟수 cur_move를 받아온다
		int x = get<0>(bfs_q.front());
		int y = get<1>(bfs_q.front());
		int cur_move = get<2>(bfs_q.front());

		bfs_q.pop();

		//현재 위치가 목적지라면 움직인 횟수를 반환해주고 종료
		if (x == M - 1 && y == N - 1)
			return cur_move;

		//현재 위치를 기준으로 움직일 수 있는 4방위에 대해 탐색
		for (int i = 0; i < 4; i++)
		{
			//i값에 따라 다음 이동 경로에 대한 정보를 xn,yn에 입력
			int xn = x + dx[i];
			int yn = y + dy[i];
			int next_move = cur_move + 1;
			//다음 이동 경로인 xn, yn의 값이 지도 범위를 벗어난다면 스킵
			if (xn < 0 || xn >= M || yn < 0 || yn >= N)	continue;

			//다음 경로가 이동 가능한 경로(map[yn][xn] ==1)이고 방문하지 않았다면 (check[yn][xn] == false)
			//다음 경로 정보를 입력한다
			if (map[yn][xn] == 1 && check[yn][xn] == false)
			{
				bfs_q.push(make_tuple(xn, yn, next_move));
				check[yn][xn] = true;
			}

		}

	}
}
int main(void)
{
	//지도를 구성할 row(N) column(M) 값을 입력받는다
	cin >> N >> M;

	//row
	for (int i = 0; i < N; i++)
	{
		//column을 구성하는 데이터를 문자열 형태로 받는다
		string tmp_input;
		cin >> tmp_input;
		//문자열을 문자로 나누어 지도 배열에 삽입
		for (int j = 0; j < tmp_input.size(); j++)
		{
			if (tmp_input[j] == '0')
				map[i][j] = false;
			else if (tmp_input[j] == '1')
				map[i][j] = true;
		}
	}
	//bfs함수를 호출하여 리턴된 결과 값을 출력
	cout << bfs() << endl;

	return 0;
}