//문제의 포인트는 루트가 1이라는 것과
//제목 그대로 "트리"의 부모 찾기이다
//혹시라도 입력된 데이터의 패턴을 보고서
//방향 그래프로 착각하는 실수를 범하지 않도록 하자
//처음으로 인접리스트를 활용한 DFS형태로 짜긴 했지만 뭔가 쫌... 엉성한듯한
#include <iostream>	//io
#include <vector>	//vector
using namespace std;

//노드 개수를 의미하는 변수 선언 및 초기화
int N = 0;
//결과가 저장될 배열 선언 및 초기화
int res[100001] = { 0 };
//인접리스트 선언
vector<int>* adj_list;

//param parent : cur 노드의 부모
//param cur : 현재 노드
void dfs(int parent, int cur)
{
	//현재 노드의 부모를 res에 저장
	//res의 인덱스는 각 노드를 의미
	res[cur] = parent;

	//현재 노드의 인접리스트 크기만큼 루프
	for (int i = 0; i < adj_list[cur].size(); i++)
	{
		//현재 노드의 다음 탐색지를 인접리스트에서 가져온다
		int next = adj_list[cur][i];
		//트리는 양방향이므로 부모노드가 아닌 자식노드를 선택할 수 있도록 플래그
		if (next != parent)
			dfs(cur, next);
	}

}
int main(void)
{
	//시간제한을 고려하여 cpp iostream 가속
	//c lib와 동기화를 끊어준다
	ios_base::sync_with_stdio(false);

	//노드의 개수를 입력받는다
	cin >> N;

	//노드의 개수+1 만큼 인접리스트 생성
	//인접리스트를 노드의 숫자별로 접근하기 위해 + 1
	adj_list = new vector<int>[N + 1];

	int input_one = 0, input_two = 0;
	//간선 정보를 입력받아 인접리스트 구성
	for (int i = 1; i < N; i++)
	{
		cin >> input_one >> input_two;

		adj_list[input_one].push_back(input_two);
		adj_list[input_two].push_back(input_one);
	}
	//dfs 탐색 시작
	dfs(0, 1);

	//결과 출력
	for (int i = 2; i <= N; i++)
		cout << res[i] << "\n";

	return 0;
}