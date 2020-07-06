/*
#include <iostream>
#include <queue>

using namespace std;

// 토마토 상태를 표시하는 인접행렬
int arr[1001][1001];
// 테스트 입력값
int M, N;
// 인접행렬에 채우는 "토마토가 익기 까지 걸린 기간" 의 기준을 day+1로 잡고 있기에
// 시작 값을 1로 설정. 왜냐하면 출력 결과 day의 값을 항상 -1로 출력하기에
// 모두 익은 상태, 즉 익기 까지의 기간이 0일 일때도 동일하게 -1 하여 출력하기 위함.
int day = 1;
// 익은 토마토로부터 사방을 검색하기 위한 방위행렬 dx, dy
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

void BFS(queue<pair<int, int>>& q)
{
	//큐(q)가 비어있을 때까지 루프
	while (!q.empty())
	{
		//큐에 남아있는 현재 노드 값을 저장
		int y = q.front().first;
		int x = q.front().second;
		//사용한 노드를 pop
		q.pop();
		//여기서 day 값을 올리고 있다면 잘못된 접근이다
		//여기서의 day값은 각 상태에 따라 4방위를 확인한 뒤 노드를 쌓고 있기 때문에 
		//큐에 쌓인 노드의 횟수는 day의 기준이 될 수 없다.
		//day++;

		//현재 노드의 위치 x y 에 대해 4방위( i 범위 ) 접근 시작
		for (int i = 0; i < 4; i++)
		{
			//dx[] dy[]의 값을 이용하여 현재 x,y 위치로 부터 좌 하 우 상 순서로 접근
			int xn = x + dx[i];
			int yn = y + dy[i];

			// 탐색 범위가 배열 범위를 넘어설 경우 무시
			if (xn < 0 || xn >= N || yn < 0 || yn >= M)
				continue;
			// 인접행렬의 현재 위치에 토마토가 없을 경우
			if (arr[yn][xn] == 0)
			{
				// 토마토로 물들인다, 단 몇 번 물들였는지( 며칠이 지났는지 ) 알기 위해 
				// 이전 상태값 arr[y][x]에 +1 된 값을 저장하도록 한다.
				// 최종 물들인 횟수는 arr에서 가장 큰 값 -1 이 된다.
				// -1은 익은 토마토의 첫 상태값이 1이기 때문이다.
				arr[yn][xn] = arr[y][x] + 1;
				// 큐에 현재 위치를 입력하여 다음 탐색을 할 수 있게 한다.
				q.push(make_pair(yn, xn));
			}
		}
	}
}

int main(void)
{
	queue<pair<int, int>> q;

	cin >> N >> M;

	//Row
	for (int i = 0; i < M; i++)
	{
		//Column
		for (int j = 0; j < N; j++)
		{
			cin >> arr[i][j];

			if (arr[i][j] == 1)
				q.push(make_pair(i, j));
		}
	}

	BFS(q);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (arr[i][j] == 0)
			{
				cout << -1 << endl;
				return 0;
			}

			if (arr[i][j] > day)
				day = arr[i][j];
		}
	}

	cout << day - 1 << endl;

	return 0;
}
*/