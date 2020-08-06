//
// 14891 톱니바퀴
//
// 조건
// - 8개의 톱니로 구성된 톱니바퀴 4개가 일렬로 놓여있다.
// - 톱니바퀴의 각 톱니는 N극 혹은 S극 중 하나이다
// - 톱니바퀴는 가장 왼쪽의 1번부터 차례대로 4번까지 존재한다
// - 톱니바퀴를 K번 회전시키려할 때, 회전은 톱니바퀴의 한칸을 기준으로 1회전으로 한다
// - 회전은 시계방향과 반시계 방향이 존재한다
// - 톱니가 서로 맞닿은 극에 따라 옆의 톱니가 회전 혹은 그대로 유지된다
//		-> 맞닿은 부분이 서로 같다면 회전하지 않고, 서로 다르다면 맞닿은 다른 바퀴는 반대 방향으로 움직인다
// - 톱니바퀴의 초기 상태와 회전 방법에 대해 제공될때, 최종 톱니바퀴의 상태에 대한 점수를 출력하라
//
// 입력
// - 1 ~ 4 line : 각 톱니바퀴의 초기 상태
// - 5 line : 회전 횟수
// - 6 ~ 6 + 회전횟수 : 톱니바퀴 번호와 회전방향
//
// 출력
// - 톱니바퀴들의 최종 상태에 따른 점수를 출력
//	- 1번 바퀴의 12시 방향이 S극이면 1점
//	- 2번 바퀴의 12시 방향이 S극이면 2점
//	- 3번 바퀴의 12시 방향이 S극이면 4점
//	- 4번 바퀴의 12시 방향이 S극이면 8점
//
// 접근
// - 하나의 바퀴가 움직이면 그 다음 바퀴들에 영향이 가는지 하드코딩

#include <iostream>	// io
#include <cstring>	// memset
#include <string>	// string
using namespace std;
//톱니바퀴의 수 정의
#define W_NUM 3
//톱니의 수 정의
#define S_NUM 7
//3시방향 톱니의 인덱스 정의
#define WHEEL_R 2
//9시방향 톱니의 인덱스 정의
#define WHEEL_L 6
//시계방향 값 정의
#define DIR_CW 1
//반시계방향 값 정의
#define DIR_R_CW -1
//톱니의 상태를 저장할 배열 선언
int wheel[W_NUM + 1][S_NUM + 1] = { 0 };
//톱니바퀴 회전 수와 결과 변수 선언 및 초기화
int N = 0, res = 0;

void precess_rotation(int w_num, int dir)
{
	//오른쪽 방향으로 돌린다
	if (dir == DIR_CW)
	{
		//배열을 오른쪽 shift하기 위해 마지막 인덱스를 저장해둔다
		int tmp_val = wheel[w_num][7];
		//마지막~1번인덱스에 대해 값 재정의
		for (int i = S_NUM; i > 0; i--)
		{
			wheel[w_num][i] = wheel[w_num][i - 1];
		}
		//0번 인덱스에 대한 처리
		wheel[w_num][0] = tmp_val;
	}
	//왼쪽 방향으로 돌린다
	else if (dir == DIR_R_CW)
	{
		//배열을 왼쪽 shift하기 위해 첫번째 인덱스를 저장해둔다
		int tmp_val = wheel[w_num][0];
		//0~마지막-1번 인덱스에 대해 값 재정의
		for (int i = 0; i < S_NUM; i++)
		{
			wheel[w_num][i] = wheel[w_num][i + 1];
		}
		//마지막 인덱스에 대한 처리
		wheel[w_num][S_NUM] = tmp_val;
	}

}
// param w_num : 바퀴 번호
// param dir : 회전 방향
void rotate_wheel(int w_num, int dir)
{
	//맞물려 돌아가는 바퀴를 위한 반대 방향값 선언 및 정의
	int r_dir = dir * -1;
	//함수 호출 시 3시방향과 9시 방향의 값을 미리 받아두기 위한 변수 선언
	int cur_R, cur_L;
	switch (w_num)
	{
	case 1:
		//오른쪽으로 돌리기 전 미리 9시 방향 값을 저장해둔다
		cur_R = wheel[0][WHEEL_R];
		//0번 바퀴와 1번 바퀴가 다른가?
		if (cur_R != wheel[1][WHEEL_L])
		{
			//0번 바퀴와 1번 바퀴가 다르고, 1번바퀴와 2번바퀴도 다른가?
			if (wheel[1][WHEEL_R] != wheel[2][WHEEL_L])
			{
				//0번 바퀴와 1번 바퀴가 다르고, 1번 바퀴와 2번바퀴도 다르고, 2번 바퀴와 3번바퀴도 다른가?
				if (wheel[2][WHEEL_R] != wheel[3][WHEEL_L])
				{
					//결과에 따른 톱니바퀴 shift
					precess_rotation(0, dir);
					precess_rotation(1, r_dir);
					precess_rotation(2, dir);
					precess_rotation(3, r_dir);
				}
				else
				{
					//결과에 따른 톱니바퀴 shift
					precess_rotation(0, dir);
					precess_rotation(1, r_dir);
					precess_rotation(2, dir);
				}
			}
			else
			{
				//결과에 따른 톱니바퀴 shift
				precess_rotation(0, dir);
				precess_rotation(1, r_dir);
			}
		}
		//0번 바퀴와 1번바퀴가 같다면 0번 바퀴에 대해서만 처리
		else
			//결과에 따른 톱니바퀴 shift
			precess_rotation(0, dir);

		break;
	case 2:
		// case 0 과 같은 형태
		cur_L = wheel[1][WHEEL_L];
		cur_R = wheel[1][WHEEL_R];
		//오른쪽방향으로 확인
		if (cur_R != wheel[2][WHEEL_L])
		{
			if (wheel[2][WHEEL_R] != wheel[3][WHEEL_L])
			{
				precess_rotation(1, dir);
				precess_rotation(2, r_dir);
				precess_rotation(3, dir);
			}
			else
			{
				precess_rotation(1, dir);
				precess_rotation(2, r_dir);
			}
		}
		else
			precess_rotation(1, dir);
		//왼쪽 방향으로 확인
		if (cur_L != wheel[0][WHEEL_R])
			precess_rotation(0, r_dir);

		break;
	case 3:
		// case 0 과 같은 형태
		cur_L = wheel[2][WHEEL_L];
		cur_R = wheel[2][WHEEL_R];
		//오른쪽방향으로 확인
		if (cur_R != wheel[3][WHEEL_L])
		{
			precess_rotation(2, dir);
			precess_rotation(3, r_dir);
		}
		else
			precess_rotation(2, dir);
		//왼쪽 방향으로 확인
		if (cur_L != wheel[1][WHEEL_R])
		{
			if (wheel[1][WHEEL_L] != wheel[0][WHEEL_R])
			{
				precess_rotation(1, r_dir);
				precess_rotation(0, dir);
			}
			else
				precess_rotation(1, r_dir);
		}

		break;
	case 4:
		// case 0 과 같은 형태
		//왼쪽 방향으로 확인
		cur_L = wheel[3][WHEEL_L];
		if (wheel[3][WHEEL_L] != wheel[2][WHEEL_R])
		{
			if (wheel[2][WHEEL_L] != wheel[1][WHEEL_R])
			{
				if (wheel[1][WHEEL_L] != wheel[0][WHEEL_R])
				{

					precess_rotation(3, dir);
					precess_rotation(2, r_dir);
					precess_rotation(1, dir);
					precess_rotation(0, r_dir);
				}
				else
				{
					precess_rotation(3, dir);
					precess_rotation(2, r_dir);
					precess_rotation(1, dir);
				}
			}
			else
			{
				precess_rotation(3, dir);
				precess_rotation(2, r_dir);
			}
		}
		else
			precess_rotation(3, dir);

		break;
	}
}

void set_res()
{
	//문제의 1~4번(0~3) 톱니바퀴의 12시 방향 값을 가져온다
	if (wheel[0][0])	res += 1;
	if (wheel[1][0])	res += 2;
	if (wheel[2][0])	res += 4;
	if (wheel[3][0])	res += 8;
}
int main(void)
{
	//톱니바퀴 상태를 입력받는다
	for (int i = 0; i <= W_NUM; i++)
	{
		string input;
		cin >> input;

		for (int j = 0; j <= S_NUM; j++)
		{
			wheel[i][j] = input[j] - '0';
		}
	}
	//톱니바퀴 회전수를 입력받는다
	cin >> N;
	//회전수만큼 톱니바퀴를 회전 시킨다
	for (int i = 0; i < N; i++)
	{
		int wheel_num = 0, dir = 0;
		cin >> wheel_num >> dir;
		//입력 값에 따라 톱니바퀴를 돌린다
		rotate_wheel(wheel_num, dir);
	}
	//최종 점수 설정
	set_res();

	cout << res << endl;
}