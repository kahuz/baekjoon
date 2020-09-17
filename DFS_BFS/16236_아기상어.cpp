//
// 조건
// - NxN크기의 공간에 물고기 M마리와 아기상어 1마리가 있다
// - 한칸에는 물고기가 최대 1마리 존재한다
// - 아기상어와 물고기는 크기를 가지고 있다
// - 아기상어는 초기에 크기가2이며, 아기상어는 1초에 상하좌우 인접한 한칸씩 이동한다
// - 아기상어는 자신의 크기보다 큰 물고기가 있는 칸을 지나갈 수 없다
// - 아기상어의 이동루틴은 아래와 같다
//	> 1 먹을 수 있는 물고기가 없다면 아기상어는 엄마상어에게 도움을 요청한다 *( 루프 종료 )
//	> 2 먹을 수 있는 물고기가 1마리라면 그 물고기를 먹으러 간다
//	> 3 먹을 수 있는 물고기가 1마리보다 많다면, 거리가 가장 가까운 물고기를 먹으러 간다
//		> 거리는 아기 상어가 있는 칸에서 물고기가 있는 칸으로 이동할때 지나야하는 칸의 최소값
//		> 거리가 가까운 물고기가 많다면 가장 위에 있는 물고기, 그러한 물고기가 여러마리라면 가장 왼쪽 물고기를 먹는다
// - * 아기상어의 이동은 1초가 걸리고, **물고기를 먹는데 걸리는 시간은 없다
// - ** 아기 상어는 자신의 크기와 같은 수의 물고기를 먹으면 크기가 자란다
// - 아기상어가 몇 초 동안 물고기를 잡아먹을 수 있는지 구하라
// 
// 입력
// - 0: 빈칸, 1,2,3,4,5,6 : 칸에 있는 물고기의 크기
// - 9: 아기 상어의 위치
// - 첫째줄 : 공간의 크기 N( 2<= N <= 20 )
// - 이후 : 공간의 상태
//
// 키포인트
// - 한번 탐색 당 아기상어가 먹을 수 있는 모든 먹이에 대해 구하고, 가장 가까운 것을 찾아줘야한다
// - 탐색은 아기상어가 먹을게 없을 동안 계속 해주어야한다
// - ** sorting 조건을 잘 확인할 것. 시뮬 조건에 맞춰 가장 가까운 거리를 제대로 구하는 것이 제일 중요하다
#include <iostream>
#include <queue>
#include <memory.h>
#include <algorithm>
#include <vector>

using namespace std;

//초기 위치 및 사이즈, 먹이를 먹고 난 뒤 갱신될 위치 및 사이즈, 먹은 횟수
int s_x = 0, s_y = 0, s_size = 2, s_e = 0;
//지도의 상태
int map[20][20] = { 0 };
int check[20][20] = { 0 };

//탐색 범위
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
//bfs탐색을 위한 큐 선언 <<x,y> 거리>
queue<pair<pair<int, int>,int>> bfs_q;
//먹을 수 있는 물고기들의 정보를 저장할 벡터 선언
vector<pair<pair<int, int>, int>> fish_v;
//입력 및 결과
int N = 0, time = 0;

void bfs()
{
	//탐색을 시작할 아기상어의 위치를 가져온다
	bfs_q.push(make_pair(make_pair(s_x, s_y),0));
	//위치에 대해 방문처리
	check[s_y][s_x] = true;

	while (!bfs_q.empty())
	{
		//탐색 위치를 가져온다
		int x = bfs_q.front().first.first;
		int y = bfs_q.front().first.second;
		int dist = bfs_q.front().second;

		//사용한 노드는 반환
		bfs_q.pop();
		//4방위에 대한 탐색시작
		for (int i = 0; i < 4; i++)
		{
			int xn = x + dx[i];
			int yn = y + dy[i];

			//지도범위를 나가거나 나보다 크다면 탐색 제외
			if (xn < 0 || xn >= N || yn < 0 || yn >= N || map[yn][xn] > s_size)	continue;
			//방문을 안했다면
			if (!check[yn][xn])
			{
				//빈칸이거나 나와 크기가 같다면
				if (map[yn][xn] == 0 || map[yn][xn] == s_size)
				{
					check[yn][xn] = true;
					bfs_q.push(make_pair(make_pair(xn, yn), dist + 1));
				}
				//먹을 수 있는 경우
				else if (map[yn][xn] < s_size)
				{
					check[yn][xn] = true;
					//다음 위치를 구하기 위해 먹을 수 있는 모든 물고기의 위치 및 거리를 기록하자
					//이동루틴을 참고하자면 크기는 중요하지 않음. 먹을 수 있는 여부로만 기록하면 됨
					fish_v.push_back(make_pair(make_pair(xn,yn),dist + 1));
					bfs_q.push(make_pair(make_pair(xn, yn), dist + 1));
				}
			}
		}
	}

}

bool compare(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	//a가 b보다 가까운가?
	if (a.second <= b.second)
	{
		//a와 b가 같은가?
		if (a.second == b.second)
		{
			//a가 b보다 위쪽인가?
			if (a.first.second <= b.first.second)
			{
				//a와 b가 같은 행인가?
				if (a.first.second == b.first.second)
				{
					//a가 b보다 왼쪽인가?
					if (a.first.first < b.first.first)
					{
						return true;
					}
					return false;
				}
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}
void play()
{
	while(true)
	{
		//bfs 탐색에 사용할 방문배열 및 물고기 벡터 초기화
		memset(check, 0, sizeof(check));
		fish_v.clear();

		bfs();
		//탐색 범위 내 먹을 수 있는 녀석이 없다
		if (fish_v.size() == 0)
		{
			cout << time << endl;
			return;
		}
		//먹을 수 있는 경우가 하나
		else if (fish_v.size() == 1)
		{
			//물고기 위치로 아기상어 위치 변경
			s_x = fish_v[0].first.first;
			s_y = fish_v[0].first.second;
			//먹은 위치를 초기화
			map[s_y][s_x] = 0;
			//먹으러 간 거리만큼 시간 갱신
			time = time + fish_v[0].second;
			//먹은 횟수 증가
			s_e++;
			//아기상어 크기만큼 먹었으면 크기 증가
			if (s_e == s_size)
			{
				s_e = 0;
				s_size++;
			}

		}
		//먹을 수 있는 경우가 여럿
		else
		{
			//가장 가까운 물고기의 거리를 찾기 위해 정렬
			sort(fish_v.begin(), fish_v.end(), compare);
			//물고기 위치로 아기상어 위치 변경
			s_x = fish_v[0].first.first;
			s_y = fish_v[0].first.second;
			//먹은 위치를 초기화
			map[s_y][s_x] = 0;
			//먹으러 간 거리만큼 시간 갱신
			time = time + fish_v[0].second;
			//먹은 횟수 증가
			s_e++;
			//아기상어 크기만큼 먹었으면 크기 증가
			if (s_e == s_size)
			{
				s_e = 0;
				s_size++;
			}
		}
	}
}
int main(void)
{
	//지도 크기르 ㄹ받아옴
	cin >> N;
	//지도 정보 갱신 및 초기 상어 위치에 대한 설정
	for(int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
				if (map[i][j] == 9)
				{
					map[i][j] = 0;
					s_x = j;
					s_y = i;
			}
		}
	//먹이냠냠
	play();

	return 0;
}