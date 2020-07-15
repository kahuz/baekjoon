//해당 문제에서 D[1]이 최대 4자리이므로 수열에 들어갈 수 있는 D[n]의 최대 수는 6자리이다
//문제 풀이는 재귀 형태의 DFS로 풀었다
//입력되는 수열이 가중치가 없는 그래프라고 생각했을때
//1차원 형태의 그래프가 생성되고 이것을 DFS, 깊이 우선 탐색으로 들어가다 중복 방문을 했을때
//그 전의 깊이를 반환하여 풀이가 가능하다.
//단순 brute force로 풀이할 경우 재귀를 활용하여 DFS 형태로 다시 풀이해보자.
#include <iostream>
#include <cmath>		//pow
using namespace std;

//수열의 첫번째 값과 다음 수열의 계산을 위한 P 변수 선언 및 초기화
int A = 0, P = 0;
//방문배열 선언 및 초기화
int check[1000000] = { 0 };
//그래프의 깊이 변수 선언 및 초기화
int dfs_depth = 1;

//param cur_num : 현재 탐색 노드의 값
void dfs(int cur_num)
{
	//탐색 노드에 처음 방문한게 아니라면
	if (check[cur_num] != 0)
	{
		//이전 깊이를 반환
		cout << check[cur_num] - 1 << endl;
		return;
	}
	//현재 노드에 탐색 깊이 값을 저장
	check[cur_num] = dfs_depth++;

	//다음 탐색 노드에 대해 계산
	int next_num = 0;

	for (int i = cur_num; i > 0; i /= 10)
		next_num += pow(i % 10, P);

	//다음 탐색노드 탐색 호출
	dfs(next_num);

}

int main(void)
{
	//수열의 첫번째 값과 다음 수열의 값을 계산하기 위한 P값을 입력받는다
	cin >> A >> P;

	//수열 탐색 시작
	dfs(A);

	return 0;
}