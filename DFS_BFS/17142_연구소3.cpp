// 17142 연구소3
// 조건 - 바이러스는 활성 상태와 비활성 상태가 있다
// - 가장 처음 모든 바이러스는 비활성 상태이며, 활성 상태인 바이러스는 1초마다 상하좌우 인접한 모든 빈칸으로 동시 복제된다
// 초기 M개 바이러스를 활성상태로 변경하려한다
// 연구소 크기는 NxN 이며, 빈칸(0), 벽(1), 바이러스(2)로 이루어져 있다.
// 활성 바이러스가 비활성 바이러스가 있는 칸으로 가면 비활성 바이러스는 활성 바이러스가 된다
// 모든 빈칸에 바이러스가 퍼지는 시간을 구하라
// * 연구소2와 달리 2는 이미 바이러스가 존재하는 칸이다. 따라서 모든 빈칸을 2로 물들이는 최소 시간을 구하면 된다
// 로직
// 1. 임의의 바이러스 M개를 고른다
// 2. 신호와 동시에 바이러스를 퍼트린다
// 3. 모든 빈칸이 바이러스로 전염되는 최소 시간을 구하자
// 입력
// line1 : 연구소(NxN)의 크기 N( 5<= N <= 50)과 바이러스의 개수 M( 1 <= M <= 10 )
// line2 ~ line(N+1) : 연구소의 시작 상태
// -> '0', '1', '2'로 이루어져 있으며 '2' == ( M<= '2')
// 접근법
// N과 M의 입력을 받은 뒤 연구소 지도와 바이러스 큐 정보를 갱신한다
// 작업 1: 임의의 2에서 M개의 바이러스를 고른다
// 작업 1은 모든 2의 위치에 대해 M개의 조합 2n_C_M 을 반복(loop)한다
//
// 작업 2: 작업1이 완료된 loop마다 바이러스를 살포 시작, 모든 빈칸이 바이러스로 전염될때까지 반복.
// 작업 2-1 :바이러스가 전염 가능한 인접지역(상.하.좌.우)에 대해 바이러스를 전염시키고 전염된 바이러스 위치를 queue에 저장한다
// 작업 2-2 : 작업 2-1을 한번 실행하는 것을 1초로 기준으로 하여
// 모든 지역이 전염될때동안 2-1을 반복, loop가 반복된 수를 갱신해준다.
//
// 작업 3 : 작업 2에대해 작업 1을 계속 반복하며, 출력할 결과를 작업 2에서 나온 전염시간을 비교하여 가장 낮은 값으로 갱신한다.
//

#include <iostream>	//io
#include <queue>	//queue
#include <vector>	//vector
#include <cstring>	//memset

using namespace std;
//바이러스 확산을 위한 큐 선언
queue<pair<int, int>> virus_q;
//바이러스 초기 위치를 저장할 벡터 선언
vector<pair<int, int>> virus_list;
//바이러스 초기 위치로부터 M개의 바이러스를 선택할 벡터 선언
vector<int> order_list;

//초기 결과값 정의
#define INIT_RES 9999999
//연구소 정보를 저장할 배열 선언 및 초기화
int map[50][50] = { 0 };
//연구소에 바이러스를 확산시킨 정보를 저장할 배열 선언 및 초기화
int spread_map[50][50] = { 0 };
//초기 빈 지역의 수를 저장할 변수 선언 및 초기화
int empty_area = 0;
//바이러스 확산에 따라 확산된 지역의 수를 저장할 변수 선언 및 초기화
int infect_area = 0;

//바이러스를 전염시킬 4방위 배열 선언 및 초기화 ( 상 우 하 좌 )
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
//조합 선택을 위한 배열 선언 및 초기화
bool b_order[10] = { 0 };

//연구소 크기 N과 바이러스의 개수 M 변수 선언 및 초기화
int N = 0, M = 0;
//결과값 변수 선언 및 초기화
int res_min_time = INIT_RES;

void spread_virus()
{
	//모든 지역을 감염시킨 시간을 저장할 변수 선언 및 초기화
	int spread_time = 1;
	// 확산시킬 바이러스( 바이러스의 수 ; order_list.size() || M)를 바이러스 확산 큐에 넣는다
	for (int i = 0; i < M; i++)
	{
		int init_x = virus_list[order_list[i]].first;
		int init_y = virus_list[order_list[i]].second;

		virus_q.push(make_pair(init_x, init_y));
		spread_map[init_y][init_x] = 1;
	}

	// 바이러스의 확산을 시작한다.
	while (!virus_q.empty())
	{
		//바이러스 큐로부터 탐색 시작 위치를 가져온다
		int x = virus_q.front().first;
		int y = virus_q.front().second;

		//탐색위치를 가져온 큐는 반환
		virus_q.pop();
		//현재 지도에서 모든 빈 지역을 감염시켰다면
		if (infect_area == empty_area)
		{
			//남은 탐색을 종료시키고
			while (!virus_q.empty())	virus_q.pop();
			//모든 지역에 바이러스를 확산할때까지 걸린 시간을 반영
			//바이러스 초기 시간을 false와 구분하기 위해 
			//0이 아닌 1로 설정했으므로 -1 해준다
			if (res_min_time >= spread_time - 1)
				res_min_time = spread_time - 1;

		}
		//바이러스의 다음 전염위치를 가져온다
		for (int i = 0; i < 4; i++)
		{
			int xn = x + dx[i];
			int yn = y + dy[i];

			//바이러스의 다음 위치가 지도를 벗어나는지 확인한다
			if (xn < 0 || xn >= N || yn < 0 || yn >= N)	continue;
			//다음 위치가 바이러스를 확산시킬 수 있는 위치면서 
			if (map[yn][xn] == 0 || map[yn][xn] == 2)
			{
				//아직 접근하지 않은 지역이라면
				if (spread_map[yn][xn] == false)
				{
					//빈 지역을 감연시킨거라면 감염시킨 지역의 수를 증가시킨다
					if (map[yn][xn] == 0)
						infect_area++;
					//바이러스를 확산 시켰음을 확인하고 확산까지 걸린 시간을 배열에 반영한다
					spread_map[yn][xn] = spread_map[y][x] + 1;
					if (spread_time <= spread_map[yn][xn])
						spread_time = spread_map[yn][xn];
					//바이러스를 확산시킬 수 있도록 큐에 삽입
					virus_q.push(make_pair(xn, yn));
				}
			}
		}
	}
}
void choose_virus(int cnt)
{
	//순번을 M개만큼 골라서 벡터에 넣었다면
	if (order_list.size() == M)
	{
		//바이러스 확산 시작
		spread_virus();
		//다음 탐색을 위해 감염시킨 지역의 수를 초기화
		infect_area = 0;
		//다음 탐색을 위해 바이러스 전염 확인 배열을 초기화
		memset(spread_map, 0, sizeof(spread_map));
		return;
	}

	//조합식으로 바이러스 M개를 선정할때까지 재귀
	for (int i = cnt; i < virus_list.size(); i++)
	{
		//아직 뽑지 않은 순서(false)라면
		if (!b_order[i])
		{
			//순서를 선택하고
			b_order[i] = true;
			//해당 순서를 벡터에 push
			order_list.push_back(i);
			//다음 순서를 매개변수로 재귀
			choose_virus(i + 1);
			//다음 순서를 선택할 수 있도록 벡터를 비우고
			order_list.pop_back();
			//다음 조합에서 해당 순번을 선택할 수 있도록 false
			b_order[i] = false;

		}
	}
}
int main(void)
{
	//연구소의 크기와 바이러스의 개수를 가져온다
	cin >> N >> M;
	//초기 연구소 지도 정보와 바이러스 위치 정보를 가져온다
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];
			if (map[y][x] == 0)
				empty_area++;
			if (map[y][x] == 2)
				virus_list.push_back(make_pair(x, y));
		}
	}

	//초기 바이러스 M개를 선택하고 전염시킬 함수 호출
	choose_virus(0);
	//바이러스를 한번도 모두 확산시키지 못했다면
	if (res_min_time == INIT_RES)
		cout << -1 << endl;
	//한번이라도 모두 확산시켰다면
	else
		cout << res_min_time << endl;

	return 0;
}
