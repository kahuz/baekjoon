#include <iostream>	//io
#include <queue>	//queue
#include <cstring>	//memset

using namespace std;

//지도를 생성할 한변의 길이 N 선언 및 초기화
int N = 0;
//지도 정보를 입력받을 배연 선언 및 초기화
int map[100][100] = { 0 };
int re_map[100][100] = { 0 };
//지도 방문 정보를 입력받을 배열 선언 및 초기화
int check[100][100] = { 0 };

//지도 탐색을 위한 방위 배열 선언 및 초기화 상 우 하 좌 
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
//BFS탐색을 위한 큐 선언
queue<pair<int, int>> bfs_q;

//param x,y: 탐색 시작 영역
//param rain_height : 탐색 영역의 기준이 될 물높이
void bfs(int x, int y, int rain_height)
{
	//탐색 시작 위치를 큐에 넣어준다
	bfs_q.push(make_pair(x, y));
	//시작 위치에 대해 방문처리를 해준다
	check[y][x] = true;

	while (!bfs_q.empty())
	{
		//큐에서 현재 좌표 값을 가져와주고
		int x = bfs_q.front().first;
		int y = bfs_q.front().second;
		//사용된 큐의 노드는 반납
		bfs_q.pop();

		//4방위를 옮겨가며 이동 가능한 위치를 탐색한다
		for (int i = 0; i < 4; i++)
		{
			int xn = x + dx[i];
			int yn = y + dy[i];

			if (xn < 0 || xn >= N || yn < 0 || yn >= N)	continue;

			//다음 지역의 높이가 쉬위보다 높고 방문하지 않은 경우
			//큐에 다음 지역에 대한 정보를 삽입하고 미리 방문처리를 해준다
			if (map[yn][xn] > rain_height && check[yn][xn] == false)
			{
				bfs_q.push(make_pair(xn, yn));
				check[yn][xn] = true;
			}
		}
	}
}

int main(void)
{
	//cin cout 입출력 스트림 가속. scanf와 printf 같은 c lib를 사용하지 않는다면 생활화하자
	ios_base::sync_with_stdio(false);
	//지도의 한 변의 값을 입력받는다
	cin >> N;

	//지도 정보를 입력받아 map배열에 값을 넣어준다
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	//물높이 0 ~ 100 에 따라 물에 잠기지 않은 영역들의 값을 저장할 배열을 선언
	int area_nums[101] = { 0 };
	//물높이(r_h)에 따라 bfs를 실행한다. 
	for (int r_h = 0; r_h <= 100; r_h++)
	{
		//현재 물높이 기준으로 물에 잠기지 않은 영역의 개수를 저장할 변수 선언 및 초기화
		int area_size = 0;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				//bfs는 전체 맵의 시작점부터 탐색 조건을 확인하여 물에 잠기지 않은 영역의 시작점에서 bfs를 호출해준다
				if (map[i][j] > r_h && check[i][j] == false)
				{
					bfs(j, i, r_h);
					//호출 후 탐색을 완료하였기에 탐색한 영역 숫자를 높여준다
					area_size++;
				}
			}
		}
		//현재 물높이에 물에 잠기지 않은 영역 값을 넣어준다
		area_nums[r_h] = area_size;
		//전체 탐색이 끝난 후 check 배열을 초기화해주어 재탐색이 가능하도록 해준다.
		memset(check, 0, sizeof(check));
	}

	//출력할 최대 영역 개수 변수 선언 및 초기화
	int max = 0;
	//area_nums에 저장된 가장 큰 값을 max에 저장
	for (int i = 0; i < 100; i++)
		if (max < area_nums[i])
			max = area_nums[i];

	cout << max << endl;
	return 0;
}