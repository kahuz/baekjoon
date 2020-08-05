// 7569 토마토
//
// 조건 
// - NxM 크기의 토마토 상자가 있고, 같은 크기의 토마토상자가 H만큼 쌓여있다.
// - 토마토상자는 익은 토마토(1)와 익지않은 토마토(0), 그리고 빈 칸(-1)으로 구성되어있다.
//	
// - 익은 토마토는 하루동안 상,하,좌,우,위,아래로 익지않은 토마토에 영향을 주어 익은 토마토로 만든다
// - 이때, 며칠이 지나면 모든 토마토가 다 익는지 그 최소 일수를 찾아내라
// - 단, 상자의 일부 칸에는 토마토가 들어있지 않을 수 있다.
//
// 입력
// - 첫줄 : 상자의 크기를 나타내는 가로( 2<= N <= 100 ), 세로 ( 2<= M <= 100 ), 와 높이( 1<= H <= 100)가 주어진다
// - 2번째 줄 ~ M * H - 1줄 : 상자에 저장된 토마토의 상태가 주어진다.
//
// 접근법
// - [H][M][N]의 3차원 배열을 이용해 정보를 입력받는다
// - 입력값 중 익은 토마토의 위치 값과 초기 날짜 값을 미리 큐에 저장한다
// - 빈 공간과 익은 토마토의 수가 상자의 모든 칸의 수와 같으면 0을 출력
// - 익은 토마토의 위치가 저장된 큐(이하 r_q)를 BFS로 돌려 탐색된 다음 위치를 r_q에 저장하고, 동시에 r_q와 방문확인 배열에 day+1값을 같이 저장해준다
// - 빈칸을 제외한 칸에 대해 방문 배열(check)이 0이 아닌 값들로 모두 채워지면 가장 높은 day값을 출력해 토마토가 모두 익은 날을 반환한다
//
// ** 상당히 비효율적으로 짠 코드.
// ** 해당 코드에서 큐 하나로 탐색하는 것으로 변경해야할 것으로 보임
//
#include <iostream>	// io
#include <queue>	// queue
#include <vector>	// vector
#include <tuple>	// tuple
using namespace std;

//토마토의 상태를 나타낼 배열 선언 및 초기화
int map[100][100][100] = { 0 };
//중복 방문 방지를 위한 배열 선언 및 초기화
int check[100][100][100] = { 0 };

//전 우 후 좌 상 하 로 탐색하기 위한 배열 선언 및 초기화
int dx[6] = { 0,1,0,-1,0,0 };
int dy[6] = { -1,0,1,0,0,0 };
int dh[6] = { 0,0,0,0,1,-1 };
//하루동안 익힐 토마토를 찾을 큐 선언
queue< pair <pair<int, int>, pair<int, int> > > bfs_q;
//익은 토마토가 저장될 큐 선언
queue< pair <pair<int, int>, pair<int, int> > > ripen_tomato_q;
//토마토 상자 크기 변수 선언 및 초기화
int N = 0, M = 0, H = 0;

//익은 토마토의 위치를 모두 조회하여 모두 익었는지, 익었다면 총 몇일이 걸렸는지 확인
int get_day()
{
	int res_day = 0;

	for (int i = 0; i < H; i++)
	{
		for (int y = 0; y < M; y++)
		{
			for (int x = 0; x < N; x++)
			{
				//만약 벽이 아닌 곳에 방문하지 못했다면(안 익은 토마토가 있다면) -1을 반환
				if (check[i][y][x] == 0 && map[i][y][x] != -1)
					return -1;
				//그렇지 않다면 방문배열에 저장된 최대 일수를 결과에 반영
				else if (check[i][y][x] > res_day)
					res_day = check[i][y][x];
			}
		}
	}
	return res_day - 1;
}
void spread_tomato()
{
	int day = 1;
	//익은 토마토에 대해 탐색 큐 선언
	while (!ripen_tomato_q.empty())
	{
		//익은 토마토의 정보를 가져온다
		int r_t_d = ripen_tomato_q.front().first.first;
		int r_t_h = ripen_tomato_q.front().first.second;
		int r_t_x = ripen_tomato_q.front().second.first;
		int r_t_y = ripen_tomato_q.front().second.second;

		ripen_tomato_q.pop();
		//토마토가 익기까지 걸린 날짜를 방문배열에 입력
		check[r_t_h][r_t_y][r_t_x] = r_t_d;
		//익은 토마토에서 전후좌우위아래 탐색을 위해 bfs_q에 정보 삽입
		bfs_q.push(make_pair(make_pair(r_t_d, r_t_h), make_pair(r_t_x, r_t_y)));
		//토마토를 익힐 다음 위치를 찾는다
		while (!bfs_q.empty())
		{
			int d = bfs_q.front().first.first;
			int h = bfs_q.front().first.second;
			int x = bfs_q.front().second.first;
			int y = bfs_q.front().second.second;

			bfs_q.pop();
			//전후좌우위아래 6곳에 대해 탐색 시작
			for (int i = 0; i < 6; i++)
			{
				int xn = x + dx[i];
				int yn = y + dy[i];
				int hn = h + dh[i];

				if (xn < 0 || xn >= N || yn < 0 || yn >= M || hn < 0 || hn >= H)	continue;
				//아직 방문하지 않았고, 안 익은 토마로의 위치라면
				if (check[hn][yn][xn] == false && map[hn][yn][xn] == 0)
				{
					//방문과 함께 토마토를 익힌 일수를 적어주고
					check[hn][yn][xn] = d + 1;
					//맵에서 토마토를 익혔다고 표시
					map[hn][yn][xn] = 1;
					//익은 토마토 큐에 삽입
					ripen_tomato_q.push(make_pair(make_pair(d + 1, hn), make_pair(xn, yn)));
				}
			}
		}
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int ripen_tomato_num = 0;
	cin >> N >> M >> H;

	for (int i = 0; i < H; i++)
	{
		for (int y = 0; y < M; y++)
		{
			for (int x = 0; x < N; x++)
			{
				cin >> map[i][y][x];

				if (map[i][y][x] == 1)
				{
					//익은 토마토의 개수를 올려준다
					ripen_tomato_num++;
					ripen_tomato_q.push(make_pair(make_pair(1, i), make_pair(x, y)));
				}
				else if (map[i][y][x] == -1)
				{
					//벽 또한 계산하기 쉽게 익은토마토 변수에 영향을 준다
					ripen_tomato_num++;
				}
			}
		}
	}
	//벽과 익은 토마토의 개수가 상자의 칸수와 같다면 0을 반환
	if (ripen_tomato_num == (N * M * H))
	{
		cout << 0 << endl;
		return 0;
	}

	spread_tomato();

	cout << get_day() << endl;
	return 0;
}