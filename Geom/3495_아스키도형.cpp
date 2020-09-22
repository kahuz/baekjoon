//
//
// 1*1 단위 정사각형으로 이루어진 보드에 '.' , '/' , '\'를 이용해서 도형을 그릴때
// '.'는 빈칸, '/'는 정사각형의 왼쪽아래-오른쪽위 선분, '\'는 왼쪽 위-오른쪽아래 선분을 나타낸다
// 주어진 문자로 그려진 도형의 넓이를 출력하는 프로그램을 작성하라
//
// '/','\'는 1x1 정삼각형을 나타내므로 두 기호(이하 대각선)의 합 / 2 가 완성된 너비가 된다
// 단, 대각선 선분으로 이루어진 도형 안에 '.'으로 빈 칸을 채워 대각선의 합 /2 보다 큰 도형을 이룰 수 있다
// 따라서 대각선 영역 안에 '.'가 포함되어 있는지 확인해주어야한다
// 단, 도형은 항상 닫히게 된다는 전제로 풀이. 예를 들어
//  /...      ./..
//  ....	  /...
//  ....	  .../
//  ....  나  ../. 와 가이 외곽선이 모두 이어지지 않는 상태가 되면 도형의 영역을 알 수 없는게 당연하므로 위 조건을 전제로 풀었다
#include <iostream>

using namespace std;

//도형이 그려질 보드 배열
char board[100][100] = { 0 };
//보드의 높이와 너비 변수
int H = 0, W = 0, res = 0;

int main(void)
{
	cin >> H >> W;

	int diagonal = 0, dot = 0;

	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			cin >> board[y][x];
			//대각선 요소가 입력되면 diagonal 값 증가
			if (board[y][x] == '\\' || board[y][x] == '/')
			{
				diagonal++;
			}

			//입력된 대각선 요소가 홀수 일때 점이 들어온다면, 해당 점은 도형 내부에 포함된다
			if (diagonal % 2 == 1)
			{
				if(board[y][x] == '.')
					dot++;
			}
		}
	}
	//입력된 대각선의 개수와 대각선 내부에 찍힌 점의 개수로 결과 너비값을 구한다
	res = (diagonal / 2) + dot;
	//출력
	cout << res << endl;

	return 0;
}