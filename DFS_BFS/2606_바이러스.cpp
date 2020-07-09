//11724번 연결요소의 개수 문제와 유사
#include <iostream>	//io
#include <queue>	//queue

using namespace std;

int N = 0;	// 입력 노드의 수
int M = 0;	// 입력 간선의 수

//bfs 탐색을 할 큐 선언
queue<int> bfs_q;

//인접행렬 선언
bool arr[100][100];
//방문한 노드를 표시하기 위한 배열 선언
bool check[100];

//return : start 노드와 연결된 모든 노드의 수
int bfs(int start)
{
	int connect_com = 0;
	//탐색 시작 위치를 큐에 삽입
	bfs_q.push(start);

	//중복 검색을 허용치 않도록 탐색 시작 위치를 표시
	check[start] = true;

	//탐색을 통해 큐에 있는 모든 노드를 반납할때까지 루프
	while (!bfs_q.empty())
	{
		//탐색을 시작할 노드를 불러온다
		int cur_node = bfs_q.front();
		//불러온 노드에 대해 반납
		bfs_q.pop();

		//cur_node와 연결된 모든 노드들에 대해 탐색
		for (int next_node = 0; next_node < N; next_node++)
		{
			//next_node에 대해 연결 여부를 인접행렬로부터 가져온다.
			bool is_connect = arr[cur_node][next_node];
			//cur_node와 next_node가 연결되어있고 방문하지 않았다면
			if (is_connect && !check[next_node])
			{
				//다음 탐색을 위해 next_node를 큐에 삽입
				bfs_q.push(next_node);
				//중복 탐색을 방지하기 위해 방문할 노드에 대해 표시
				check[next_node] = true;
				//탐색 시작 노드를 기준으로 연결된 노드를 찾았으므로 connect_nom 값을 증가
				connect_com++;
			}
		}

	}
	//탐색 시작(start) 노드와 연결된 모든 노드의 수를 반환
	return connect_com;
}
int main(void)
{
	cin >> N >> M;

	//간선의 정보를 입력받아 인접행렬에 삽입
	for (int i = 0; i < M; i++)
	{
		int input_one = 0, input_two = 0;
		//간선의 정보를 입력받는다
		cin >> input_one >> input_two;
		//입력받은 간선의 정보를 토대로 인접행렬에 표시
		//방향이 없는 그래프이므로 양방향으로 표시
		//입력 값의 기준이 1부터 시작이므로 인접행렬에서는
		//배열 참조값에 맞추어 -1을 해준다
		arr[input_one - 1][input_two - 1] = 1;
		arr[input_two - 1][input_one - 1] = 1;
	}

	//문제의 기준이 1번 노드와 연결된 노드들을 찾는 것이므로
	//bfs함수의 매개변수(시작 위치)를 0으로 삽입
	//1이 아닌 0인 이유는 배열을 편하게 참조하기 위함
	cout << bfs(0) << endl;

	return 0;
}