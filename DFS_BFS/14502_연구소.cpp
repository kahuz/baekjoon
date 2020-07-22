// 시간제한은 2초 메모리 제한은 512Mb
// 주어지는 탐색범위, 맵의 크기는 3~8
// 시간과 메모리가 매우 넉넉한 문제
// 3개의 벽을 세우는 모든 경우의 수에 대해 구하고
// 벽이 세워진 지도에 BFS로 바이러스를 퍼트린 후
// 해당 지도에서 바이러스가 퍼지지 않은 영역에 대해 구하여 반환
// 반환된 결과들을 특정 변수에 저장
// 이후 전달되는 바이러스가 퍼지지 않은 영역에 대해 비교하여
// 가장 큰 값을 출력해주면 해결
#include <iostream>		// io
#include <queue>		// queue

using namespace std;
//맵의 세로(N)과 가로(M)의 입력변수 선언 및 초기화
int N = 0, M = 0;
//지도 정보를 저장할 변수 선언 및 초기화
int map[8][8] = { 0 };
//바이러스를 확산시킨 지도 정보를 저장할 변수 선언 및 초기화
int re_map[8][8] = { 0 };

//4방위 방향을 탐색하기 위한 배열 선언 및 초기화
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

//바이러스 확산을 위한 큐 선언
queue<pair<int, int>> virus_q;
//바이러스 확산 후 안전지역에 대한 값을 비교하여 가장 큰 값을 저장할 변수 선언 및 초기화
int max_area = 0;

void map_copy();
void find_area();
void spread_virus();
void build_wall(int wall_num);

//벽이 세워진 지도(map)에 바이러스를 확산시킬 임시 지도(re_map) 생성
void map_copy()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			re_map[i][j] = map[i][j];

}
//바이러스가 확산된 영역에서 안전 영역을 찾아 이전 값과 비교하여 가장 큰 값을 저장
void find_area()
{
	int area_num = 0;

	//지도 전체에 대해 순차검색으로 안전지역을 구하여 area_num 값을 올려준다
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (re_map[i][j] == 0)
				area_num++;
		}
	}
	//이전에 저장된 안전영역(max_area)와 현재 찾은 안전영역(area_num)을 비교해 큰 값을 max_area에 저장
	if (max_area < area_num)
		max_area = area_num;
}

//BFS로 바이러스를 확산시킨다
void spread_virus()
{
	//지도에서 바이러스의 시작지점을 찾아준다
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			//바이러스 시작지점을 찾이면 바이러스 확산을 위해 bfs큐에 삽입
			//함수를 모듈화해도 좋음, 본인은 같은 목적을 가진 내용이기에 하나의 함수에 담아둠
			if (re_map[i][j] == 2)
			{
				virus_q.push(make_pair(j, i));

				//모든 큐가 비워질때까지 루프
				while (!virus_q.empty())
				{
					//큐에서 현재 노드의 좌표값을 받아와 다음 탐색지점을 찾을 수 있게 한다
					int x = virus_q.front().first;
					int y = virus_q.front().second;

					//사용된 노드는 반납
					virus_q.pop();
					//다음 탐색지점에 대해 확인
					for (int i = 0; i < 4; i++)
					{
						int xn = x + dx[i];
						int yn = y + dy[i];

						if (xn < 0 || xn >= M || yn < 0 || yn >= N)	continue;

						//바이러스를 기준으로 사방위 안에 안전지역이 있다면 바이러스를 확산
						if (re_map[yn][xn] == 0)
						{
							re_map[yn][xn] = 2;
							//확산된 지역을 큐에 넣고 다음 탐색을 할 수 있게 한다
							virus_q.push(make_pair(xn, yn));
						}

					}

				}
			}
		}
	}
	//모든 바이러스가 확산되었다면 find_area함수로 남은 안전지역을 확인
	find_area();

}
//재귀를 이용하여 지도에 3개의 벽을 세우는 모든 경우의 수 확인
void build_wall(int wall_num)
{
	//벽이 3개 세워졌다면
	if (wall_num == 3)
	{
		//바이러스를 확산시켜볼 임시 지도를 생성
		map_copy();
		//바이러스 확산 루틴 실행
		spread_virus();
		return;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			//빈 영역이라면
			if (map[i][j] == 0)
			{
				//지도에 벽을 세우고
				map[i][j] = 1;
				//벽 카운터를 올린다
				build_wall(wall_num + 1);
				map[i][j] = 0;
			}
		}
	}
}

int main(void)
{
	//iostream의 가속을 위해 아래 구문 추가. 본 문제에서는 필요가 없지만
	//cpp iostream만을 사용할 경우 습관처럼 추가하자
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	//입력받은 지도정보를 map 변수에 저장
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	//3개의 벽을 세우기 위해 build_wall 함수 호출, build_wall 함수 내에 나머지 함수 루틴들이 들어가있음
	build_wall(0);
	//계산된 최대 안전지역 크기를 출력
	cout << max_area << endl;
	return 0;
}