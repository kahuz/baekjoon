// 구현 방법에 대해 어렵게 접근했던 문제
// 정말 간단하게 모든 탐색 경우를 생각하여
// 6자리 숫자를 만든 것들에 대해 나열하면 되는 문제이다
// 알고리즘 유형이 백트레킹이라하여 기존 DFS/BFS 문제 풀이와 다르게 접근할 필요가 없다.
#include <iostream>	// io

using namespace std;
//숫자판 가로 세로 생성
int N = 5;
//입력받을 숫자판의 배열 선언 및 초기화
int map[5][5] = { 0 };
//DFS 탐색을 통해 얻은 6자리 결과값에 대해 중복 방문 방지 배열
//DFS를 통해 만들 숫자는 6자리이다. 
//즉 6자리를 넘는 경우는 나올 수 없기에 배열의 크기를 100만으로 설정
bool check[1000000] = { 0 };
//탐색 방향을 결정할 배열 선언 및 초기화
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
//중복되지 않은 6자리 숫자의 개수
int res = 0;

//param x ,y : 방문할 위치
//param sum : 최종 6자리가 될 매개변수
//param depth : 탐색횟수를 가리킬 매개변수, depth가 6일때 6자리가 완성되므로 break
void dfs(int x, int y, int sum, int depth)
{
	//depth가 6일때. 즉, 6자리를 구하였을때
	if (depth > 5)
	{
		//해당 값에 대해 방문한적이 없으면. 즉, 처음 보는 6자리라면
		if (check[sum] == false)
		{
			//6자리에 대해 확인했다는 표시와
			check[sum] = true;
			//찾은 6자리의 개수를 증가
			res++;
		}
		return;
	}

	//현 지점에서 4방위로 탐색할 수 있도록 루프
	for (int i = 0; i < 4; i++)
	{
		//다음 탐색 지점을 정하고
		int xn = x + dx[i];
		int yn = y + dy[i];
		//탐색 지점이 입력 범위 밖이라면 스킵
		if (xn < 0 || xn >= N || yn < 0 || yn >= N)	continue;
		//입력범위 내라면 다음 지점의 좌표와
		//현재 구한 자리수에 대해 세팅, 탐색 횟수를 넘겨준다
		dfs(xn, yn, sum * 10 + map[yn][xn], depth + 1);
	}

}
int main(void)
{
	//숫자판 크기만큼 입력을 받는다
	for (int i = 0; i < N; i++)
	{
		//숫자판 정보를 입력
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	}

	//숫자판의 모든 지점에 대해 DFS 탐색 시작
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			dfs(j, i, map[i][j], 1);
	}
	//결과 출력
	cout << res << endl;
	return 0;
}