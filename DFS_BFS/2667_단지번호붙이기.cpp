#include <iostream>		//io
#include <string>		//string
#include <vector>		//vector
#include <queue>		//queue
using namespace std;

//단지 정보가 입력될 인접행렬 선언
int map[25][25];
//중복 방문을 방지하기 위한 행렬 선언
int check[25][25];
//map 크기를 정할 입력값 N 선언 및 초기화
int N = 0;

//인접 단지를 검색하기 위한 방위행렬 선언 및 초기화
//상 우 하 좌 시계방향 순.
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1,  0 };

//BFS 탐색을 위한 큐 선언 queue<x,y>
queue<pair<int, int>> bfs_q;
vector<int> res;

void remake_map();
int bfs(int start_x, int start_y, int label);

void remake_map()
{
	int label = 1;
	//입력된 지도 범위 전체에 대해 탐색
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//입력된 지도 데이터에서 단지의 위치를 확인하여 bfs 탐색
			if (map[i][j] == 1 && check[i][j] == 0)
			{
				res.push_back(bfs(j, i, label++));
			}
		}
	}

	//버블정렬을 이용하여 결과 값을 오름차순으로 정렬하여 res에 저장한다
	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res.size() - 1; j++)
		{
			if (res[j] > res[j + 1])
			{
				int tmp_value = res[j];
				res[j] = res[j + 1];
				res[j + 1] = tmp_value;
			}

		}
	}
}
//param start_x. start_y : 탐색 시작 위치
//param label : 디버깅을 위한 라벨 색인용 변수
//return : 단지를 이루는 집의 개수를 반환
int bfs(int start_x, int start_y, int label)
{
	int house_num = 1;
	//탐색 시작 위치를 큐에 삽입
	bfs_q.push(make_pair(start_x, start_y));
	//디버깅을 위해 check배열에 라벨 값 입력
	check[start_y][start_x] = label;

	//큐가 비게 될 때 까지 루프
	while (!bfs_q.empty())
	{
		//큐에 입력된 x,y 좌표를 받아온다
		int x = bfs_q.front().first;
		int y = bfs_q.front().second;
		//가져온 노드를 반납
		bfs_q.pop();

		//탐색 시작 위치로부터 방위행렬로 접근하기 위한 루프
		for (int i = 0; i < 4; i++)
		{
			//상 우 하 좌 순으로 접근하기 위해 현재 위치에 방위행렬 값을 더한다
			int xn = x + dx[i];
			int yn = y + dy[i];

			//탐색 범위가 지도 범위를 넘어갔을 경우 continue로 스킵
			if (xn < 0 || xn >= N || yn < 0 || yn >= N) continue;

			//방문하지 않은 집에 접근
			if (map[yn][xn] == 1 && check[yn][xn] == 0)
			{
				//큐에 방문할 위치를 넣어준다
				bfs_q.push(make_pair(xn, yn));
				//방문 위치에 대한 색인작업
				check[yn][xn] = label;
				//단지를 이루는 집의 개수를 올려준다
				house_num++;

			}

		}
	}
	return house_num;
}

int main(void)
{
	////map 크기 정보를 받아온다
	cin >> N;

	vector<string> map_data(N);

	//단지에 대한 정보를 문자열로 받아온다
	for (int i = 0; i < N; i++)
	{
		cin >> map_data[i];
		//문자열로 받은 데이터를 인접행렬에 입력
		//입력받는 변수는 int이고 넣는 값은 문자이므로
		//데이터 값을 동일하게 처리하기 위해 - '0'을 해준다
		for (int j = 0; j < map_data.size(); j++)
			map[i][j] = map_data[i].at(j) - '0';
	}

	//BFS 탐색을 위한 함수 호출
	remake_map();

	//결과 단지 수 출력
	cout << res.size() << endl;

	//단지별 집 갯수 출력
	for (int i = 0; i < res.size(); i++)
		cout << res.at(i) << endl;

	return 0;
}