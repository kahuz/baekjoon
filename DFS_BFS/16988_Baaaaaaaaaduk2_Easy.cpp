//DFS와 BackTracking을 이용해 풀 수 있는 문제
//문제의 요지는 다음과 같다
//1. 입력으로 주어지는 바둑판은 고정된다.
//2. 고정된 바둑판에 2개의 수를 놓을 수 있다.
//3. 내가 임의로 2개의 수를 놓게 되었을 때, 상대방을 가장 많이 잡을 수 있는 경우를 찾아라
//4. 상대방을 잡는 조건은 상대방이 나에게 둘러쌓여 더이상 연결된 바둑돌을 놓을 수 없는 상태이다.

#include <iostream>	//io
#include <queue>	//queue
#include <cstring>	//memset
using namespace std;
//바둑판 크기 변수 선언 및 초기화
int N = 0, M = 0;
//바둔판 배열 선언 및 초기화
int map[20][20] = { 0 };
//내가 놓을 바둑판의 위치에 대해 중복 방문을 확인할 배열 선언 및 초기화
int check[20][20] = { 0 };
//상대방이 놓은 돌을 탐색할 때 중복 방문을 확인할 배열 선언 및 초기화
int check_black[20][20] = { 0 };


//탐색 시 사용할 4방위 배열 선언 및 초기화 , 우 하 좌 상
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

//bfs 탐색을 위한 큐 선언
queue<pair<int, int>> bfs_q;

//결과를 출력할 변수 선언 및 초기화
int res = 0;

//func : 내가 돌을 둔 이후 상대방의 돌을 잡을 수 있는지 판단하기 위한 함수
//param x,y : 탐색 시작 위치
int black_bfs(int x, int y)
{
	//내가 잡을 수 있는 흑돌의 개수를 저장할 변수 선언 및 초기화
//흑돌 위치에서 시작하기 초기값은 1로 시작
	int get_black_num = 1;
	//탐색 도중 0을 만났을 시 get_black_num을 반환하지 않게 하기 위한 변수
	//0을 만나고 바로 함수를 return할 수도 있찌만
	//그 경우 남은 상대돌(2)에 대해 재탐색을 해야함과 그에 맞는 조건을 새로 짜주어야하기 때문
	bool is_move = false;
	//현재 위치에 대해 방문했음을 표시
	check_black[y][x] = true;
	//현재 위치를 큐에 사입
	bfs_q.push(make_pair(x, y));
	//큐에 탐색 노드가 없을때까지 루프
	while (!bfs_q.empty())
	{
		//탐색할 노드의 정보를 가져온다
		int x = bfs_q.front().first;
		int y = bfs_q.front().second;
		//사용한 노드는 반납
		bfs_q.pop();
		//현재 위치에 대해 4방위로 탐색
		for (int i = 0; i < 4; i++)
		{
			//다음 탐색 위치에 대해 값 설정
			int xn = x + dx[i];
			int yn = y + dy[i];
			//다음 탐색 위치가 범위를 벗어나면 continue
			if (xn < 0 || xn >= M || yn < 0 || yn >= N)	continue;

			//상대방 돌이 움직일 수 있다면
			//is_move를 true로 바꾸어 흑돌의 개수를 반환하지 않을 수 있게 한다
			if (map[yn][xn] == 0)
			{
				is_move = true;
			}
			//연결된 흑돌이 존재한다면 다음 탐색지점으로 정하고, 잡을 수 있는 흑돌의 개수를 증가시킨다
			else if (map[yn][xn] == 2 && check_black[yn][xn] == false)
			{
				check_black[yn][xn] = true;
				bfs_q.push(make_pair(xn, yn));
				get_black_num++;
			}
		}
	}
	//탐색 도중 0을 만난적이 없을 시 탐색한 상대방 돌의 수를 반환
	if (!is_move) return get_black_num;
	//탐색 도중 0을 만났다면 0을 반환
	return 0;
}

//func : 내가(1) 돌을 놓을 때 사용할 함수
void play_go(int x, int y, int cnt)
{
	//내가 돌을 2개 놓았다면
	if (cnt == 2)
	{
		//탐색 결과를 반환받을 변수 선언 및 초기화
		int get_black_num = 0;
		//바둑판의 모든 위치에 대해 상대 돌이 존재하는지 루프
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				//바둑판에서 상대 돌을 발견하였고 아직 탐색하지 않은 돌이라면
				if (map[i][j] == 2 && check_black[i][j] == false)
				{
					//bfs탐색을 통해 상대 돌의 상태에 따라 결과값을 반환받는다
					get_black_num += black_bfs(j, i);

				}
			}
		}
		//반환받은 결과가 이전 결과보다 크다면 출력 결과 변수에 저장
		if (res < get_black_num)
			res = get_black_num;

		//현재 바둑판에 대해 탐색을 마쳤고, 이후 재탐색을 위해 방문표시 배열을 초기화
		memset(check_black, 0, sizeof(check_black));

		return;
	}

	//바둑판의 모든 위치에 대해 돌을 놓을 수 있는지 루프
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			//빈 공간이며 아직 조합상 돌을 놓아보지 않은 위치라면
			if (map[i][j] == 0 && check[i][j] == false)
			{
				//현재 위치에 대해 돌을 놓아보았음을 표시
				check[i][j] = true;
				//돌이 있음을 표시
				map[i][j] = 1;
				//다음 돌을 놓거나 bfs탐색으로 이어지도록 함수 호출
				play_go(j, i, cnt + 1);
				//돌을 모두 놓고 bfs탐색이 끝났다면 돌을 회수
				check[i][j] = false;
				map[i][j] = 0;
			}
		}
	}
}

int main(void)
{
	//바둑판 크기 정보를 가져온다
	cin >> N >> M;
	//바둑판의 배열 상태를 받아온다
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			//받은 바둑판 배열 상태를 저장
			cin >> map[y][x];
		}
	}
	//바둑판에 대해 탐색 시작
	play_go(0, 0, 0);
	//결과 반환
	cout << res << endl;

	return 0;
}