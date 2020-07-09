#include <iostream>	//io
#include <queue>	// queue

using namespace std;

#define DFS 0
#define BFS 1
//노드의 개수와 간선의 개수를 입력받기 위한 변수 선언 및 초기화
int N = 0, M = 0;

//BFS 탐색을 위한 큐 선언
queue<int> bfs_q;
//탐색을 위한 인접행렬 선언 
bool arr[1000][1000];
//이미 거처간 간선인지 확인하기 위한 배열 선언
bool check[1000];

void dfs(int cur_node);
void bfs(int cur_node);

int solution(int type)
{
	int connect_num = 0;

	//입력된 모든 노드에 대해 탐색을 한다.
	for (int i = 0; i < N; i++)
	{

		//탐색하지 않은 노드에 대해 탐색 시작
		if (check[i] == false)
		{
			//입력 type 값에 따라 dfs 혹은 bfs 호출
			switch (type)
			{
			case DFS:
				dfs(i);
				//i와 연결된 모든 노드를 DFS로 거쳐간 뒤 연결요소의 값을 상승 시켜준다.
				connect_num++;
				break;
			case BFS:
				bfs(i);
				//i와 연결된 모든 노드를 BFS로 거쳐간 뒤 연결요소의 값을 상승 시켜준다.
				connect_num++;
				break;
			default:
				break;
			}
		}
	}
	return connect_num;
}

void dfs(int cur_node)
{

	//탐색 노드의 중복 접근을 방지하기 위해 표시
	check[cur_node] = true;
	//현재 노드에 대해 다음 탐색지를 찾는다
	for (int next_node = 0; next_node < N; next_node++)
	{
		//현재 노드에 대한 입접행렬 정보를 가져온다.
		bool is_next = arr[cur_node][next_node];
		//next_node가 가리킨 노드가 현재 노드와 연결된 노드임과 동시에
		//탐색하지 않은 노드일 경우
		if (is_next && !check[next_node])
		{
			//다음 행선지를 DFS 함수에 넣어 다음 탐색을 할 수 있도록 한다.
			dfs(next_node);
		}
	}

}
//return : 연결요소의 수
void bfs(int cur_node)
{
	//탐색 노드의 중복 접근을 방지하기 위해 표시
	check[cur_node] = true;

	//탐색할 노드를 삽입
	bfs_q.push(cur_node);
	//탐색할 노드가 없을때까지 루프
	while (!bfs_q.empty())
	{
		//탐색할 현재 노드를 큐에서 가져온다.
		int cur_node = bfs_q.front();
		//사용된 노드는 반납
		bfs_q.pop();

		//현재 노드에 대해 다음 탐색지를 찾는다
		for (int next_node = 0; next_node < N; next_node++)
		{
			//현재 노드에 대한 인접행렬 정보를 가져온다
			bool is_next = arr[cur_node][next_node];

			//next_node가 가리킨 노드가 현재 노드와 연결된 노드임과 동시에
			//탐색하지 않은 노드일 경우
			if (is_next && check[next_node] == false)
			{
				//큐에 다음 행선지를 넣어준다.
				bfs_q.push(next_node);
				//다음 행선지에 대해 방문 표시를 해준다.
				check[next_node] = true;
			}
		}

	}
}

int main(void)
{
	cin >> N >> M;

	//입력받은 간선의 개수를 토대로 간선의 정보를 저장
	for (int i = 0; i < M; i++)
	{

		int tmp_one = 0, tmp_two = 0;
		cin >> tmp_one >> tmp_two;

		//무방향 그래프이므로 입력값에 대해 양방향 모두 표시
		//인접행렬로 색인을 할 것이기에 입력값 -1의 배열에 값을 채워준다
		arr[tmp_one - 1][tmp_two - 1] = true;
		arr[tmp_two - 1][tmp_one - 1] = true;
	}

	//BFS 탐색을 호출하고 결과값을 cout으로 출력
	//cout << BFS() << endl;
	//DFS 탐색을 호출하고 결과값을 cout으로 출력
	cout << solution(DFS) << endl;

	return 0;
}