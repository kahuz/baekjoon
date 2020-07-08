#include <iostream>	// io
#include <queue>	// queue
#include <cstring>	// memset

using namespace std;

//문제의 입력값에 대한 변수 선언 및 초기화
int N = 0, M = 0, V = 0;
//입력받은 간선의 정보를 저장할 인접행렬 선언
//인접행렬의 크기는 문제에서 주어진 최대 제한값 1000x1000으로 선언하였지만
//실제 사용되는 크기는 입력값 N을 기준으로 사용한다.
//편의상 1000x1000으로 선언했을 뿐 입력 N에 대해 선언 및 초기화하여도 상관없다.
int arr[1000][1000];
//이미 탐색을 완료한 노드에 대해 중복된 결과를 내지 않기 위한 배열 선언
bool check[1000];

//BFS 탐색을 위한 큐 생성
queue<int> bfs_q;

//param v : 탐색 위치
void DFS(int v)
{
	//방문한 위치에 대해 라벨링
	check[v] = true;

	//현재 방문 위치를 출력. v는 배열 인덱스 값이기에 문제에서 요구하는 출력형태를 맞추기 위해 + 1
	cout << v + 1 << " ";

	//탐색 범위는 i는 노드의 시작 - 끝
	for (int i = 0; i < N; i++)
	{
		//현재 탐색위치를 인접행렬의 행(row)로 기준을 잡고 
		//연결된 간선들에 대한 정보인 열(column)의 정보를 확인하여
		//arr[현재위치][연결노드] == 1 이면 노드가 연결된 것을 인지하고 다음 탐색을 진행한다.
		if (arr[v][i] == 1 && !check[i])
		{
			DFS(i);
		}
	}

}


//param v: 탐색 시작 위치
void BFS(int v)
{
	//방문 노드를 큐에 삽입
	bfs_q.push(v);

	//방문 노드에 대해 라벨링
	check[v] = true;

	//bfs_q가 모두 비워질때까지 루프
	while (!bfs_q.empty())
	{
		//현재 방문한 노드의 정보를 가져온다
		int n = bfs_q.front();

		//방문 노드 결과 출력
		cout << n + 1 << " ";

		//방문을 완료하였으므로 노드를 제거해준다.
		bfs_q.pop();

		//탐색 범위는 i는 노드의 시작 - 끝
		for (int i = 0; i < N; i++)
		{
			//현재 탐색위치를 인접행렬의 행(row)로 기준을 잡고 
			//연결된 간선들에 대한 정보인 열(column)의 정보를 확인하여
			//arr[현재위치][연결노드] == 1 이면 노드가 연결된 것을 인지하고 다음 탐색을 진행한다.
			if (arr[n][i] == 1 && !check[i])
			{
				//다음 노드를 큐에 넣어준다.
				bfs_q.push(i);
				//다 대해 라벨링
				check[i] = true;
			}
		}
	}

}
int main(void)
{
	//정점의 개수(N), 간선의 개수(M), 탐색 시작 위치(V)에 대해 입력을 받아온다.
	cin >> N >> M >> V;

	//그래프를 이루는 간선의 정보를 입력받아 인접행렬에 값을 넣어준다.
	for (int i = 0; i < M; i++)
	{
		int tmp_one = 0;
		int tmp_two = 0;

		cin >> tmp_one >> tmp_two;

		//문제에서 간선의 방향이 양방향이기에 그에 맞게끔 인접행렬 값을 입력해준다.
		//입력값은 인덱스의 시작 번호가 1이므로 input-1 값으로 행렬에 접근한다.
		arr[tmp_one - 1][tmp_two - 1] = 1;
		arr[tmp_two - 1][tmp_one - 1] = 1;
	}

	//DFS 함수 호출
	//입력 V는 방문 노드 순서를 1부터 시작하도록 하지만
	//정의된 DFS에서는 배열 인덱스를 기준으로 0부터 시작하므로 -1을 해준다.
	DFS(V - 1);
	//DFS 함수 종료 후 BFS 탐색을 위해 check배열 초기화
	memset(check, 0, sizeof(check));
	//DFS 출력결과와 BFS출력결과를 구분해준다.
	cout << endl;
	//BFS 함수 
	//입력 V는 방문 노드 순서를 1부터 시작하도록 하지만
	//정의된 BFS에서는 배열 인덱스를 기준으로 0부터 시작하므로 -1을 해준다.
	BFS(V - 1);

	return 0;
}