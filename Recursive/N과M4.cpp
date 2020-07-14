//재귀 연습용 문제
//N과M시리즈에서 본 문제까지 완료하였다면 재귀에 대해 어느정도 이해하고 있다고 본다
//코드를 보기 전 노트를 이용해 숫자의 흐름을 파악하여 구현할 수 있도록 하자
//만약 필기로 모든 과정을 확인하였는데도 구현이 되지 않는다면
//아래 코드를 참고하자
#include <iostream>	//io

using namespace std;

//입력받을 수열의 범위(N)과 수열의 길이(M)을 입력받기 위한 변수 선언 및 초기화
int N = 0, M = 0;
//결과가 저장될 배열 선언 및 초기화
int res_arr[8] = { 0 };

//param cur_num : 현재 호출된 값
//param cnt : 재귀 호출 횟수
void recursive_func(int cur_num, int cnt)
{
	//재귀 호출횟수가 M에 도달하면
	if (cnt == M)
	{
		//res_arr에 저장된 M개의 수열을 출력
		for (int res_i = 0; res_i < M; res_i++)
		{
			cout << res_arr[res_i] << " ";
		}
		//다음 수열을 구분하기 위한 개행문자 출력
		cout << "\n";
		return;
	}

	//i값의 상태를 기억하여
	//다음 재귀 시 i값부터 시작할 수 있도록 한다
	for (int i = cur_num; i <= N; i++)
	{
		res_arr[cnt] = i;
		recursive_func(i, cnt + 1);
	}
}
int main(void)
{
	//수열 값의 범위와 수열의 길이를 입력 받는다
	cin >> N >> M;
	//수열을 출력하기 위한 함수 호출
	recursive_func(1, 0);
	return 0;
}