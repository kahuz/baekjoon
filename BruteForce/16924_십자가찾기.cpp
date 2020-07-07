/*
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

#define STAR 1
//테스트 입력값
int N = 0, M = 0;
//십자가 위치가 표시될 인접행렬
int input_arr[101][101];
int res_arr[101][101];

//특정 위치로 부터 사방을 확인하기 위한 방위행렬 dx, dy
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

int check_cross(int x, int y)
{
	// 십자가 중앙으로부터 각 방위로 뻗은 선의 길이를 저장할 배열
	// 가장 작은 길이를 가진 값이 십자가의 크기가 될 것
	// 만약 가장 작은 값이 0이라면 십자가를 만들 수 없는 조건이며,
	// 네곳 모두 1이상이라면 길이 1이상의 십자가이다.
	int dot_sizes[] = { 0,0,0,0 };
	// 리턴할 십자가의 길이, 초기 값은 십자가 최대 길이인 100으로 설정
	int cross_size = 100;

	for (int i = 0; i < 4; i++)
	{
		// i 값에 따라 좌 하 우 상 순으로 십자가 크기를 확인하기 위한 변수
		int xn = x;
		int yn = y;

		// 각 방위에 대한 길이를 저장하기 위한 변수
		int dot_size = 0;

		while (true)
		{
			// 방위행렬 dx,dy는 한쪽 방향에 대해 한칸의 크기를 가지고 잇으므로
			// while이 진행되는 동안 dx, dy 값을 더해줌으로써 십자가 크기를 탐색하도록 한다
			xn += dx[i];
			yn += dy[i];

			// 만약 xn과 yn 값이 입력된 행렬의 크기를 벗어난다면 while을 break
			if (xn < 0 || xn >= M || yn < 0 || yn >= N)	break;

			// 현재 위치가 십자가를 구성하는 별이라면 계속 탐색
			if (input_arr[yn][xn] == STAR)
				dot_sizes[i] = ++dot_size;
			// 그렇지 않다면 while을 break
			else
				break;

		}
	}

	// 탐색된 4방위의 십자가 길이를 비교해 가장 작은 값을 cross_size에 저장한다.
	// 만약 가장 작은 값이 0이라면 십자가를 이루지 못한다.
	for (int i = 0; i < 4; i++)
	{
		if (cross_size >= dot_sizes[i])
			cross_size = dot_sizes[i];
	}

	return cross_size;

}

int main(void)
{
	queue<pair<int, int>> q;
	vector<tuple<int, int, int>> res_v;

	cin >> N >> M;

	//Row
	for (int i = 0; i < N; i++)
	{
		//Column
		for (int j = 0; j < M; j++)
		{
			char tmp_input = 0;

			cin >> tmp_input;

			//입력 값에 대해 인접행렬에 라벨링 작업을 해준다.
			//큰 의미는 없으며, 이후 십자가 표시를 쉽게 하기 위해 숫자로 바꾼 것.
			if (tmp_input == '*')
			{
				input_arr[i][j] = STAR;
				//십자가 여부를 확인하기 위해 q에 좌표 삽입
				q.push(make_pair(i, j));
			}
		}
	}

	//입력된 값 중 별이 찍혀있다면 루프, 없다면 리턴
	while (!q.empty())
	{
		//입력된 별의 위치를 가져온다.
		int cur_star_x = q.front().second;
		int cur_star_y = q.front().first;
		//check_cross 함수를 통해 십자가 크기를 가져온다.
		//만약 존재하지 않는다면 0을 리턴
		int cross_size = check_cross(cur_star_x, cur_star_y);

		// 사용한 노드를 반납
		q.pop();
		//cross_size가 0보다 크다면 십자가가 존재하므로 결과 출력을 위해 결과 큐(res_q)에 값을 출력 순으로 저장
		if (cross_size > 0)
			res_v.push_back(make_tuple(cur_star_y, cur_star_x, cross_size));
	}

	//입력 배열과 결과 배열을 비교하기 위한 변수 선언
	bool is_same = true;

	if (!res_v.empty())
	{
		int cross_num = res_v.size();

		for (int i = 0; i < cross_num; i++)
		{
			int cross_y = get<0>(res_v[i]);
			int cross_x = get<1>(res_v[i]);
			int cross_length = get<2>(res_v[i]);

			res_arr[cross_y][cross_x] = STAR;

			for (int j = 0; j < 4; j++)
			{
				int cross_xn = cross_x;
				int cross_yn = cross_y;

				for (int k = 0; k < cross_length; k++)
				{
					cross_xn += dx[j];
					cross_yn += dy[j];

					res_arr[cross_yn][cross_xn] = STAR;
				}
			}
		}

		// 입력 배열과 결과 배열이 같은지 확인하기
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (input_arr[i][j] != res_arr[i][j])
					is_same = false;
			}
		}

		if (is_same)
		{
			cout << cross_num << endl;

			for (int i = 0; i < cross_num; i++)
			{
				//문제 출력기준은 좌표를 1,1부터 시작하지만 저장된 값을 배열을 기준으로 0,0 부터 시작하므로 좌표 값에 대해 +1 해준다
				cout << get<0>(res_v[i]) + 1 << " ";
				cout << get<1>(res_v[i]) + 1 << " ";
				cout << get<2>(res_v[i]) << endl;

			}
		}
		else
			cout << -1 << endl;

	}
	else // 찾은 십자가가 없을 경우
		cout << -1 << endl;

	return 0;
}
*/