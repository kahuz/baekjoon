//잘못 접근한 코드
//문제에서 색종이를 붙이는 가장 적은 횟수를 구하라에 대해
//가장 큰 종이부터 붙여나가면 되겠구나? 로 접근하였다.
//하지만 이 문제는 최적의 해를 구하는 방식이기에 당연히 잘못된 반례들이 속출...
//#include <iostream>	//io
//
//using namespace std;
//
//int map[10][10] = { 0 };
//int check[10][10] = { 0 };
//int check2[10][10] = { 0 };
//int attached[10][10] = { 0 };
//
//int papers[6] = {0,5,5,5,5,5};
//
//void attach_paper(int x, int y)
//{
//	int column = attached[y][x];
//
//	if (column == 1)
//	{
//		papers[1] = papers[1] - 1;
//		check2[y][x] = true;
//		return;
//	}
//	else
//	{
//		if (column >= attached[y][x + 1])
//		{
//			int row = 1;
//			int yn = y;
//
//			//다음 row에 대해 확인
//			for (int i = 1; i < column; i++)
//			{
//				yn = y + i;
//
//				if (attached[yn][x] >= column)
//					row++;
//			}
//
//			if (row == column)
//			{
//				papers[row] = papers[row] - 1;
//
//				for (int i = 0; i < row; i++)
//				{
//					for (int j = 0; j < column; j++)
//					{
//						check2[y+i][x+j] = true;
//					}
//				}
//			}
//			else
//			{
//				for (int i = 0; i < row; i++)
//				{
//					papers[1] = papers[1] - 1;
//					check2[y + i][x] = true;
//				}
//			}
//		}
//		else
//		{
//			papers[1] = papers[1] - 1;
//			check2[y][x] = true;
//			return;
//		}
//	}
//}
//
//int search_row(int x, int y, int column_depth, int depth)
//{
//	if (attached[y][x] == false )
//		return 0;
//
//	check[y][x] = true;
//
//	if(depth >= column_depth)
//	{
//		return column_depth;
//	}
//
//
//	int res = search_row(x, y + 1, column_depth, depth + 1);
//
//	if (res == 0)
//		return attached[y][x] = depth;
//	else
//	{
//		if (res >= column_depth)
//		{
//			attached[y][x] = column_depth;
//			return column_depth;
//		}
//		else
//		{
//			attached[y][x] = res;
//			return res;
//		}
//	}
//}
//
//int search_column(int x, int y, int depth)
//{
//	if (map[y][x] == false)
//	{
//		if (depth > 5)
//			depth = 5;
//		return depth;
//	}
//	int res = 0;
//	res = search_column(x + 1, y, depth + 1);
//
//	return res;
//}
//
//int main(void)
//{
//	ios_base::sync_with_stdio(false);
//	int res = 0;
//
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			cin >> map[i][j];
//		}
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			if(map[i][j] == true )
//				attached[i][j] = search_column(j, i, 0);
//		}
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			if (attached[i][j] >= 1 && check[i][j] == false)
//			{
//				search_row(j, i, attached[i][j], 1);
//			}
//		}
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			if (attached[i][j] >= 1 && check2[i][j] == false)
//			{
//				attach_paper(j,i);
//			}
//		}
//	}
//
//	for (int i = 1; i < 6; i++)
//	{
//		if (papers[i] < 0)
//		{
//			res = -1;
//			break;
//		}
//		else {
//			res += 5 - papers[i];
//		}
//	}
//	cout << res << endl;
//
//	return 0;
//}

//제대로 접근한 코드
//가진 종이를 사용할 수 있는 모든 경우의 수를 다 확인하여
//최종적으로 가장 적은 결과값이 나오는 경우를 리턴하였다
//문제 풀이를 위한 로직을 생각하기는 어렵지 않으나
//많은 조건들로 인해 구현이 어려웠던 문제
#include <iostream>		//io

using namespace std;
//종이를 표시할 지도 배열 선언 및 초기화
int map[10][10] = { 0 };
//종이를 붙였음을 알리고 중복으로 붙이지 않게 하기 위한 배열 선언 및 초기화
int check[10][10] = { 0 };
//크기별 종이의 개수를 저장할 배열 선언 및 초기화
int papers[6] = { 0,5,5,5,5,5 };
//지도에 붙여야할 종이의 개수를 저장할 변순 선언 및 초기화
int paper_cnt = 0;
//결과 변수 선언 및 초기화
//종이를 최대 25장 붙일 수 있으므로 26으로 설정
int res = 26;

//param x,y,param : check 배열에 표시할 범위를 지정하기 위한 변수
//param state : check 배열에 표시할 true, false 값
void check_attach(int x, int y, int size, int state)
{
	for (int i = y; i < y + size; i++)
	{
		for (int j = x; j < x + size; j++)
		{
			check[i][j] = state;
		}
	}
}

//param x,y : 종이를 붙일 위치
//param size : 종이의 크기
//return : x,y 위치에 size의 종이를 붙일 수 있는 여부를 나타냄
bool is_attach(int x, int y, int size)
{
	//더이상 붙일 수 있는 size의 종이가 없거나 x,y가 범위를 넘어갔을때 false
	if (papers[size] == 0 || x + size > 10 || y + size > 10)
		return false;

	for (int i = y; i < y + size; i++)
	{
		for (int j = x; j < x + size; j++)
		{
			//size 종이를 붙이려는 곳이 0이 포함되거나 이미 이전에 붙인 곳이라면 false 반환
			if (map[i][j] == 0 || check[i][j] == true)
				return false;
		}
	}
	//종이를 붙일 수 있다면 true 반환
	return true;
}

//param x,y : 종이를 붙일 위치
//param attached_cnt : 현재까지 붙인 종이의 개수
void attached_paper(int x, int y, int attached_cnt)
{
	//모든 종이를 다 덮었다면
	if (paper_cnt == 0)
	{
		//이전에 종이를 붙인 수와 비교하여 더 작은 값을 저장
		if (res > attached_cnt)
			res = attached_cnt;

		return;
	}
	//종이를 붙일 다음 위치를 위한 변수 선언 및 초기화
	int xn = 0, yn = 0;
	//지도 전체를 조회하여 종이를 붙일 수 있는 위치를 xn,yn에 저장
	for (int i = 0; i < 10; i++)
	{
		//이중 for문을 나가기 위한 변수
		bool is_out = false;
		for (int j = 0; j < 10; j++)
		{
			//종이를 붙여야하고, 아직 붙이지 않았다면 xn,yn 값을 설정
			if (map[i][j] == 1 && check[i][j] == false)
			{
				xn = j;
				yn = i;
				is_out = true;
				break;
			}
		}
		if (is_out) break;
	}
	//모든 크기의 종이에 대해 부착여부 확인 및 부착
	for (int p_size = 1; p_size < 6; p_size++)
	{
		//p_size의 종이를 붙일 수 있는지 확인
		if (is_attach(xn, yn, p_size))
		{
			//p_size 크기의 종이 개수를 하나 더 줄인다
			papers[p_size] -= 1;
			//xn,yn위치에 p_size의 종이를 붙였음을 알린다
			check_attach(xn, yn, p_size, true);
			//현재 남은 종이의 개수에 현재 붙인 종이의 개수만큼 빼준다
			paper_cnt -= (p_size * p_size);

			attached_paper(xn, yn, attached_cnt + 1);
			//다음 경우를 확인하기 위해 위에 사용한 변수들을 이전 값으로 되돌린다
			check_attach(xn, yn, p_size, false);
			paper_cnt += (p_size * p_size);
			papers[p_size] += 1;
		}
	}
	return;
}

int main(void)
{
	//입력받은 지도 정보를 저장
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			cin >> map[y][x];

			if (map[y][x] == 1)
				paper_cnt++;
		}
	}
	//지도에 종이가 없다면 0을 출력
	if (paper_cnt == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	//종이를 붙이기 위한 탐색 시작
	attached_paper(0, 0, 0);
	//사용된 종이의 개수를 출력
	//만약 종이를 사용하여 모두 붙일 수 있었다면 res 값 출력
	if (res < 26 && res > -1)
		cout << res << '\n';
	else
		//종이를 사용하여 모두 붙일 수 없었다면 -1 출력
		cout << -1 << '\n';


	return 0;
}