//백트래킹 형태로 접근하는 문제 ( 사실 DFS로 푸는 많은 문제들이 결과적으로 백트래킹 형태를 띈다고 생각한다 )
// 1. 현재 접근 요소가 이전에 접근한 요소에 해당되는가
// 2. 배열 범위를 넘어서는가
#include <iostream>
#include <string>

using namespace std;

//이미 접근한 알파벳인지 확인하기 위한 배열 선언 및 초기화
bool exist_alphbet[26] = { 0 };
//이미 접근한 위치인지 확인하기 위한 배열 선언 및 초기화
bool check[20][20] = { 0 };
//영문자 보드판을 위한 배열 선언 및 초기화
char board[20][20] = { 0 };

//다음 알파벳을 탐색하기 위한 방위행렬 선언 및 초기화 , 우 하 좌 상
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

//입력 알파벳 배열의 row, column 값을 가지는 변수 선언 및 초기화
int R = 0, C = 0;
//탐색 최대값을 가질 변수 선언 및 초기화
int res = 0;


//param x,y : 현재 위치 변수
//param depth : 탐색 깊이 변수
void dfs(int x, int y, int depth)
{
	//보드판의 현재 위치 알파벳을 가져온다 ( 'A' -> 0 으로 가져와서 exist_alphbet을 알파벳순으로 접근하여 확인
	int cur_alphabet = board[y][x] - 'A';
	//해당 알파벳을 가져온 적이 있다면 반환
	if (exist_alphbet[cur_alphabet] == true)
		return;
	//해당 알파벳을 가져왔다고 표시
	exist_alphbet[cur_alphabet] = true;
	//현재 위치를 방문했음을 표시
	check[y][x] = true;
	//다음 탐색지를 정하기 위해 루프
	for (int i = 0; i < 4; i++)
	{
		//다음 탐색지 좌표를 가져온다
		int xn = x + dx[i];
		int yn = y + dy[i];

		//다음 위치가 탐색범위를 벗어나면 무시
		if (xn < 0 || xn >= C || yn < 0 || yn >= R)	continue;
		//다음 위치를 탐색한 적이 없다면 탐색 호출
		if (check[yn][xn] == false)
			dfs(xn, yn, depth + 1);
	}
	//최종 depth값을 가져온다.
	//가장 깊게 들어간 값이 res에 저장된다
	if (res < depth)
		res = depth;
	//현재 위치에 대해 다음 탐색을 모두 마친 상태라면
	//현재 위치에 대한 알파벳 정보와 방문 정보를 모두 초기화한다
	exist_alphbet[cur_alphabet] = false;
	check[y][x] = false;

}

int main(void)
{
	//보드판의 row와 column 값을 입력받는다
	cin >> R >> C;
	//보드판을 조회
	for (int row = 0; row < R; row++)
	{
		//보드판의 정보를 문자열 형태로 받아
		string tmp_row;
		cin >> tmp_row;
		//column에 해당하는 문자열 점보를 board 배열에 표시
		for (int column = 0; column < C; column++)
		{
			board[row][column] = tmp_row[column];
		}
	}
	//dfs탐색 시작 , 현재 위치를 카운트하고 시작하므로 depth값을 1로 시작
	dfs(0, 0, 1);
	//결과 출력
	cout << res << endl;

	return 0;
}