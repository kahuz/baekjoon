#include <iostream>	// io
#include <queue>	// queue
#include <tuple>	// tuple
#include <cstring>	// memset
using namespace std;
int T = 0;	//테스트 케이스 횟수를 입력받을 변수
int N = 0;	//체스판 한 변의 길이
//int cur_loc[2] = {0,0};	// 현재 위치
//int dest_loc[2] = { 0,0 }; //목적지 위치
int cur_x = 0, cur_y = 0;
int dest_x = 0, dest_y = 0;
//방문 확인을 위한 check배열
bool check[300][300];
//8방위 방문을 위한 방위행렬 선언 및 초기화
int dx[8] = { -2,-1,1,2,2,1,-1,-2 };
int dy[8] = { -1,-2,-2,-1,1,2,2,1 };
//bfs 탐색을 위한 큐 선언, 이동할 체스판 x,y 좌표와 이동횟수 move를 저장한다.
queue < tuple<int, int, int>> bfs_q;
//param x , y : 탐색을 시작할 위피
int move_knight(int start_x, int start_y)
{
	//탐색 시작 위치를 큐에 삽입
	bfs_q.push(make_tuple(start_x, start_y, 0));
	//현재 위치를 check배열에 표시
	check[start_y][start_x] = true;
	//탐색할 큐가 없을때까지 루프
	while (!bfs_q.empty())
	{
		//큐에서 탐색할 위치의 기준이 되는 x,y값을 가져온다
		int x = get<0>(bfs_q.front());
		int y = get<1>(bfs_q.front());
		;
		//8방위 탐색을 위한 루프
		for (int i = 0; i < 8; i++)
		{
			int xn = x + dx[i];
			int yn = y + dy[i];

			//탐색할 위치가 체스판을 벗어나면 스킵
			if (xn < 0 || xn >= N || yn < 0 || yn >= N)	continue;
			//나이트가 움직인 횟수를 올려준다.
			int cur_move = get<2>(bfs_q.front()) + 1;

			//이동한 위치가 목적지라면 이동한 횟수를 리턴하고 함수 종료
			//if (xn == dest_loc[0] && yn == dest_loc[1])
			if (xn == dest_x && yn == dest_y)
				return cur_move;
			//이동한 위치가 목적지가 아니라면 이동한 위치 정보를 bfs_q에 삽입하여
			//다음 탐색을 이어갈 수 있도록 해주고
			//check 배열에 현재 위치를 방문했음을 표시하여 중복 방문을 방지한다.
			else
			{
				if (!check[yn][xn])
				{
					bfs_q.push(make_tuple(xn, yn, cur_move));
					check[yn][xn] = true;
				}
			}
		}
		//가져온 노드를 반납
		bfs_q.pop();
	}
}
int main(void)
{
	//테스트 케이스 횟수 입력
	cin >> T;
	//결과 출력을 위한 큐 선언
	queue<int> res_q;
	while (T--)
	{
		memset(check, 0, sizeof(check));

		//이전에 사용하고 남은 큐를 모두 비워준다.
		while (!bfs_q.empty()) { bfs_q.pop(); }
		//체스판 한 변의 길이
		cin >> N;
		//현재 나이트의 위치
		//cin >> cur_loc[0] >> cur_loc[1];
		cin >> cur_x >> cur_y;
		//나이트의 목표 위치
		//cin >> dest_loc[0] >> dest_loc[1];
		cin >> dest_x >> dest_y;
		//현재 위치와 목적지가 같을 경우 함수를 호출하지 않고 0을 삽입
		//if (cur_loc[0] == dest_loc[0] && cur_loc[1] == dest_loc[1])
		if (cur_x == dest_x && cur_y == dest_y)
		{
			res_q.push(0);
		}
		else
		{
			//BFS 탐색 함수 호출
			int move_num = move_knight(cur_x, cur_y);
			res_q.push(move_num);
		}
	}
	//res_q에 삽입된 결과값 출력
	while (!res_q.empty())
	{
		cout << res_q.front() << endl;
		res_q.pop();
	}
	return 0;
}