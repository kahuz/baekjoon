//
// 접근
// - 주어진 인접 행렬로부터 연결된 모든 요소에 대한 인접행렬을 구한다
// - 인접행렬로부터 탐색 위치를 받고 연결된 모든 요소를 탐색하여 현재 위치와 연결되어있음을 표시하자
// - DFS를 이용하여 해결
#include <iostream>

using namespace std;

int arr[100][100] = { 0 };
int res[100][100] = { 0 };
int check[100][100] = { 0 };
int N = 0;

//param start : 탐색 시작 위치
//param next : 현재 탐색 위치
void search_node(int start, int next)
{
	//현재 탐색 위치(next)가 start에서부터 탐색하여 도달하였기에
	//start와 next는 연결되어 있는 것
	check[start][next] = 1;
	res[start][next] = 1;

	//현재 탐색위치(next)로부터 아직 방문하지 않은 다음 연결요소가 있는지 확인
	for (int i = 0; i < N; i++)
	{
		if (check[start][i] == 0 && arr[next][i] == 1)
		{
			search_node(start, i);
		}
	}
}
int main(void)
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int tmp = 0;
			cin >> tmp;
			arr[i][j] = tmp;
		}
	}
	//아직 방문하지 않은 노드를 탐색 시작위치로 search_node함수를 호출한다
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (check[i][j] == 0 && arr[i][j] == 1)
			{
				search_node(i, j);
			}
		}
	}
	//결과 출력
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}