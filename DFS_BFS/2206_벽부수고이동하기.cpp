//길목마다 벽이 세워져있을 수 있는 NxM 지도에서
//최단 경로로 목적지에 도달했을때의 이동횟수를 구하는 문제
//벽을 한번 부수고 이동할 수 있다는 가정이 있기에
//NxM 행렬에 대해 벽을 한번 부순 모든 경우를 찾아
//벽을 부수지 않은 경우와 벽을 부순 모든 경우 중
//최단 경로의 값을 리턴하면 되는 문제
//시간 복잡도를 계산해보고 문제에 접근하도록 하자
//brute force 형태로도 답을 구할 순 있지만... 결과는 ㅎㅎ...
#include <iostream>	//io
#include <queue>	//queue
#include <string>	//string
#include <tuple>	//tuple

using namespace std;

//이미 부쉈다면 상태값 CRASH
#define CRASH	1
//아직 부수지 않았다면 상태값 NOT_CRASH
#define NOT_CRASH 0 

//지도의 세로(N) 가로(M)크기를 받을 변수 선언 및 초기화
int N = 0, M = 0;

//초기 지도정보를 받을 배열 선언 및 초기화
int map[1000][1000] = { 0 };

//이미 방문한 위치를 확인할 배열 선언 및 초기화
//check배열의 구성은 [y][x][carsh]로 구성된다
//crash는 역할은 벽을 부수고 해당 지점(x,y)에 도착했느냐(1)와
//벽을 부수지 않고 도착했냐(0) 두 상태를 가지기 위해서이다
//이미 벽을 부수고 왔다면 이후 벽을 부술 수 없기에 더이상 나아갈 수 없고
//벽을 부수지 않고 해당 지점에 도착했다면 추가로 벽을 부술 수 있기에 보다 나아갈 수 있다
//각 배열의 원소는 방문하지 않았음(0)과 몇번의 걸음 끝에 방문하였음( n : 정수 )로 구성된다
int check[1000][1000][2] = { 0 };

//경로 탐색을 위한 방위 배열 선언 및 초기화
int dx[4] = { 0, 1 , 0 ,-1 };
int dy[4] = { -1, 0, 1, 0 };
//최단거리의 값들을 저장할 배열 선언 및 초기화
int res_arr[1000][1000] = { 0 };
//최단거리의 값을 가질 변수 선언 및 초기화
int res = 0;
//최단 경로 탐색에 사용할 bfs 큐 선언
//큐의 인자값은 x, y, crash(벽을 부쉈는가 부수지 않았는가)로 구성
queue<tuple<int, int, int>> bfs_q;

//return : 최단경로의 값, 만약 목적지에 도착 못했다면 -1 반환
int find_path()
{
	//탐색 시작 위치(x,y)와 아직 벽을 부수지 않았음(NOT_CRASH)을 삽입
	bfs_q.push(make_tuple(0, 0, NOT_CRASH));
	//벽을 부수지않고(NOT_CRASH) 시작 위치를 방문(1). 방문 값은 현재 이동 횟수( 초기 1 )를 의미
	check[0][0][NOT_CRASH] = 1;

	//탐색할 노드가 없을때까지 루프
	while (!bfs_q.empty())
	{
		//탐색 위치의 값과 해당 값에 대한 벽을 부순 여부(crash)값을 받아온다
		int x = get<0>(bfs_q.front());
		int y = get<1>(bfs_q.front());
		int crash = get<2>(bfs_q.front());
		//사용한 노드는 반환
		bfs_q.pop();

		//현재 위치가 목적지라면 이동한 횟수를 반환
		//crash는 목적지에 도착했을때까지 벽을 부쉈는가(NOT_CRASH)와 부수지 않았는가(CRASH) 두가지 상태로 받아올 수 있다
		//하지만 결론적으로는 return을 하게 되기에 가장 먼저 도착한 상태값의 결과를 반환하게 된다
		if (x == M - 1 && y == N - 1)
			return check[y][x][crash];
		//4방위에 대한 탐색 시작
		for (int i = 0; i < 4; i++)
		{
			//다음 탐색 위치를 설정
			int xn = x + dx[i];
			int yn = y + dy[i];
			//다음 탐색 위치가 탐색 범위를 벗어나면 스킵
			if (xn < 0 || xn >= M || yn < 0 || yn >= N)	continue;

			//다음 탐색 위치에 벽이 있고, 아직 벽을 한번도 부수지 않았다면(NOT_CRASH)
			if (map[yn][xn] == 1 && crash == NOT_CRASH)
			{
				//다음 탐색 위치 값과 벽을 부수고 도착했음을 알려준다
				bfs_q.push(make_tuple(xn, yn, CRASH));
				//다음 위치에 벽을 부수고 갈 것이기에 방문 여부 배열은 yn, xn, CRASH으로 접근
				//현재까지 걸은 수 + 1을 넣어준다
				check[yn][xn][CRASH] = check[y][x][crash] + 1;
			}
			//다음 탐색 위치가 빈 공간이고, 아직 방문하지 않았다면
			if (map[yn][xn] == 0 && check[yn][xn][crash] == 0)
			{
				//다음 탐색 위치와 현재까지 벽을 부순 여부를 큐에 삽입
				bfs_q.push(make_tuple(xn, yn, crash));
				//다음 탐색 위치에 현재 걸음 수 + 1을 해준다
				check[yn][xn][crash] = check[y][x][crash] + 1;
			}
		}

	}

	return -1;


}

int main(void)
{
	//지도의 크기 정보를 가져온다
	cin >> N >> M;
	//지도 정보를 삽입하기 위한 루틴
	for (int i = 0; i < N; i++)
	{
		string tmp_input;
		cin >> tmp_input;
		//문자열로 받을 것이기에 - '0'을 통해 정수값이 입력될 수 있도록 한다
		for (int j = 0; j < tmp_input.size(); j++)
		{
			map[i][j] = tmp_input[j] - '0';
		}
	}
	//탐색 시작
	res = find_path();
	//결과 출력
	cout << res << endl;

	return 0;
}