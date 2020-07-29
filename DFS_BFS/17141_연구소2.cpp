// 17141 연구소2
// 조건 - NxN크기의 연구소는 빈칸(0,2), 벽(1)으로 이루어져있고
// 빈칸의 일부는 바이러스를 놓을 수 있는 칸(2) ( 바이러스 칸은 빈칸으로도 취급된다 )
// 바이러스는 1초에 상, 하, 좌, 우 인접한 칸으로 "동시에" 복제 된다
// 이때 모든 빈칸(0,2)에 바이러스를 퍼트리는 최소 시간을 구해보자
// 로직
// 1. 임의의 위치에 바이러스 M개를 놓는다
// 2. 신호와 동시에 바이러스를 퍼트린다
// 3. 모든 빈칸이 바이러스로 전염되는 최소 시간을 구하자
// 입력
// line1 : 연구소(NxN)의 크기 N( 5<= N <= 50)과 바이러스의 개수 M( 1 <= M <= 10 )
// line2 ~ line(N+1) : 연구소의 시작 상태
// -> '0', '1', '2'로 이루어져 있으며 '2' == ( M<= '2')
// 접근법
// N과 M의 입력을 받은 뒤 연구소 지도를 갱신하고 M개의 Queue를 생성
// 작업 1: M개의 바이러스를 임의의 '2'에 위치 시킨다
// 작업 1은 모든 2의 위치에 대해 M개의 조합 2n_C_M 을 반복(loop)한다
//
// 작업 2: 작업1이 완료된 loop마다 바이러스를 살포 시작, 모든 빈칸이 바이러스로 전염될때까지 반복.
// 작업 2-1 :바이러스가 전염 가능한 인접지역(상.하.좌.우)에 대해 바이러스를 전염시키고 전염된 바이러스 위치를 queue에 저장한다
// 작업 2-2 : 작업 2-1을 한번 실행하는 것을 1초로 기준으로 하여
// 모든 지역이 전염될때동안 2-1을 반복, loop가 반복된 수를 갱신해준다.
//
// 작업 3 : 작업 2에대해 작업 1을 계속 반복하며, 출력할 결과를 작업 2에서 나온 전염시간을 비교하여 가장 낮은 값으로 갱신한다.
//
#include <iostream>	// io
#include <queue>	// queue
#include <vector>	// vector
#include <tuple>	// tuple
#include <cstring>	// memset

#define INIT_RES 9999999
using namespace std;
//연구소 크기와 바이러스의 개수 변수 선언 및 초기화
int N = 0, M = 0;
//초기 연구소 지도 배열 선언 및 초기화
int map[50][50] = { 0 };
//선정한 바이러스 위치를 확인할 배열 선언
int choose_virus_map[50][50] = { 0 };
//바이러스를 전염시킨 상태를 확인할 배열 선언 및 초기화 ( 전염되지 않은 곳은 0 , 전염된 곳은 전염까지 걸린 시간-1부터시작 )
int virus_map[50][50] = { 0 };
//바이러스를 전염시킬 4방위 배열 선언 및 초기화 ( 상 우 하 좌 )
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
//M개의 바이러스의 전염을 확산시킬 queue 선언 ( x, y )
queue<pair< int, int>> virus_q;
//초기 바이러스 위치를 저장할 vector 선언 ( x, y )
vector<pair<int, int>> virus_pos;
//저장된 virus_pos로부터 M개의 바이러스를 뽑아오기 위한 vector 선언 ( virus_pos의 index값 )
vector<int> virus_order;
//빈 지역의 개수 변수 선언 및 초기화
int empty_area = 0;
//최종 출력 결과 변수 선언 및 초기화
int res_min_time = INIT_RES;
//조합식 접근 시 virus_pos로 중복 접근을 막기 위한 배열 선언 및 초기화
bool d_visited[10] = { 0 };

void spread_virus()
{
	//탐색까지 걸린 시간으로 초기 값은 1로 시작
	int cur_res = 1;
	//바이러스의 전염된 지역의 수를 나타낼 변수. 초기 빈지역과 같은 값이여야만 모든 지역을 감염시켰음을 확인됨
	int virus_num = 0;

	//choos_virus로부터 선택된 초기 바이러스 위치들을 탐색 큐에 삽입
	for (int i = 0; i < M; i++)
	{
		int init_x = virus_pos[virus_order[i]].first;
		int init_y = virus_pos[virus_order[i]].second;

		virus_q.push(make_pair(init_x, init_y));
		virus_map[init_y][init_x] = 1;
		virus_num++;
	}

	//모든 전염이 완료될때까지
	while (!virus_q.empty())
	{
		//현재 바이러스의 위치 및 확산 시간 정보를 가져온다
		int x = virus_q.front().first;
		int y = virus_q.front().second;
		//가저온 큐는 반환
		virus_q.pop();

		//바이러스가 접근할 수 있는 4방위에 대해 탐색 시작
		for (int i = 0; i < 4; i++)
		{
			//다음 탐색 위치에 대해 선정
			int xn = x + dx[i];
			int yn = y + dy[i];

			//다음 탐색 위치가 배열을 벗어나는지 확인
			if (xn < 0 || xn >= N || yn < 0 || yn >= N)	continue;

			//지도상 빈 지역이면서
			if (map[yn][xn] == 0 || map[yn][xn] == 2)
			{
				//바이러스를 전염시키지 않은 지역이라면
				if (virus_map[yn][xn] == 0)
				{
					virus_map[yn][xn] = virus_map[y][x] + 1;
					cur_res = virus_map[yn][xn];
					virus_q.push(make_pair(xn, yn));
					virus_num++;
				}
			}
		}
	}
	//바이러스가 전염되지 않은 구역과 비교하기 위해 바이러스 전염시간을 1초부터 시작하였으므로 -1 해준다
	cur_res -= 1;
	//모든 빈지역을 전염시켰다면
	if (virus_num == empty_area)
	{
		//현재 전염시킨데 걸린 시간이 이전 결과값보다 작을때 덮어씌운다
		if (res_min_time > cur_res)
			res_min_time = cur_res;
	}
}

void choose_virus(int cnt)
{
	//바이러스의 개수만큼 위치 선정이 되면 바이러스 전염 시작
	if (virus_order.size() == M)
	{
		spread_virus();
		memset(virus_map, 0, sizeof(virus_map));
		return;
	}
	//2n_C_M 조합으로 바이러스 위치를 선택해간다
	for (int i = cnt; i < virus_pos.size(); i++)
	{
		if (!d_visited[i]) {
			d_visited[i] = true;

			virus_order.push_back(i);
			choose_virus(i +1);
			virus_order.pop_back();
			d_visited[i] = false;
		}
	}
}

int main(void)
{
	//연구소의 크기와 바이러스의 개수를 입력받는다
	cin >> N >> M;

	//초기 맵 상태 갱신
	//value == 0 , 2 는 빈 지역을 뜻하므로 empty_area 값을 상승시키고
	//바이러스 활성 가능지역인 2에 대해 초기 바이러스 위치를 init_virus queue에 저장한다
	for (int map_y = 0; map_y < N; map_y++)
	{
		for (int map_x = 0; map_x < N; map_x++)
		{
			cin >> map[map_y][map_x];

			if (map[map_y][map_x] == 0)
			{
				empty_area++;
			}
			else if (map[map_y][map_x] == 2)
			{
				virus_pos.push_back(make_pair(map_x, map_y));
				empty_area++;
			}
		}
	}
	//초기 바이러스 M개를 선택하고 전염시킬 함수 호출
	choose_virus(0);
	//결과값이 한번도 변하지 않았다면 전염시킬 수 없는 상태이기에 -1 반환
	if (res_min_time == INIT_RES)
		cout << -1 << endl;
	else
		cout << res_min_time << endl;
	return 0;
}