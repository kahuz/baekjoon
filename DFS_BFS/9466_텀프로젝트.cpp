#include <iostream>		//io
#include <cstring>		//memset
using namespace std;

//테스트 케이스와 노드의 수를 저장할 변수 선언 및 초기화
int T = 0, N = 0;
//결과값을 저장할 변수 선언, 초기화는 테스트 루프에서 진행
int res;
//인전행렬 선언 및 초기화
int arr[100001] = { 0 };
//각 노드(배열의 인덱스)의 방문 정보를 저장할 배열 선언, 원소는 탐색시 몇번째로 방문했는지를 저장
int check[100001] = { 0 };
//각 노드(배열의 인덱스)의 탐색시 탐색 첫번째 노드를 저장할 배열 선언 및 초기화
int start_nodes[100001] = { 0 };

//param start : 탐색 시작 노드
//param cur : 현재 방문한 노드
//param depth : 현재 노드까지 방문한 깊이, 만약 사이클이 시작 노드 ~ 현재 노드까지라면 
//모든 노드가 사이클을 이루고 있으므로 사이클에 포함된 노드수 - depth = start_nodes[cur]이 1이므로 사이클에 포함된 노드수가 된다 
//만약 사이클이 시작 이후의 노드 ~ 현재 노드라면 사이클에 포함된 노드수 - depth = "경로상 사이클의 제외된 노드 수" 가 된다
int dfs(int start, int cur, int depth)
{
	//이미 현재 노드에 방문했다면
	if (check[cur] > 0)
	{
		//시작 노드로 사이클이 진행되지 않고 방문했다면
		//이미 사이클을 이룬 노드에 접근하는 것이므로
		//현재 노드는 사이클이 아니다
		if (start_nodes[cur] != start)
			return 0;

		//사이클에 포함된 노드 수
		return depth - check[cur];
	}

	//현재 노드의 탐색 시작 노드를 저장
	start_nodes[cur] = start;
	//탐색경로 상 현재 노드에 몇번째로 방문했는지 저장
	check[cur] = depth;
	//다음 탐색으로 진입
	return dfs(start, arr[cur], depth + 1);
}

int main(void)
{
	//cpp iostream 가속을 위한 c lib 동기화 제거
	ios_base::sync_with_stdio(false);
	//테스트 케이스 수를 입력받는다
	cin >> T;

	//테스트 케이스 수만큼 루프
	while (T--)
	{
		//테스트 케이스 별 결과값 저장을 위한 초기화
		res = 0;

		//노드의 수를 입력받는다
		cin >> N;

		//각 노드별 간선 정보를 입력받는다
		for (int i = 1; i <= N; i++)
			cin >> arr[i];

		//각 노드별 탐색 진행
		for (int i = 1; i <= N; i++)
		{
			//check[i] == false, i노드를 아직 탐색하지 않았다면
			if (!check[i])
			{
				//dfs 탐색 후 사이클에 해당하는 노드의 수를 리턴
				res += dfs(i, i, 1);
			}
		}
		//결과값 출력
		cout << N - res << endl;
		//사용된 배열 초기화, arr은 입력시 초기화되므로 제외
		memset(check, 0, sizeof(check));
		memset(start_nodes, 0, sizeof(start_nodes));
	}
	return 0;
}