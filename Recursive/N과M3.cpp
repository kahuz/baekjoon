//재귀 연습용 문제
//본 문제는 코드를 보는것은 큰 의미가 없으며
//코드를 보기 전 노트를 이용해 숫자의 흐름을 파악하여 구현할 수 있도록 하자
//만약 필기로 모든 과정을 확인하였는데도 구현이 되지 않는다면
//아래 코드를 참고하자
#include <iostream>		//io

using namespace std;

//수열의 범위N과 수열의 길이 M을 입력받을 변수 선언 및 초기화
int N = 0, M = 0;
//수열의 길이만큼 채워진 결과를 저장할 배열 선언 및 초기화
int res_arr[7] = { 0 };

//param cnt : 재귀의 호출 횟수
void recursive_func(int cnt)
{
	//재귀가 수열의 길이만큼 호출되었다면
	if (cnt == M)
	{
		//수열의 길이 값만큼 ( 0 ~ M-1 ) res_arr에서 출력
		for (int i = 0; i < M; i++)
		{
			cout << res_arr[i] << " ";
		}
		//다음 수열을 구분할 수 있게 개행문자 출력
		cout << "\n";

		return;
	}

	//i = 1부터 시작하여 현재 사용한 값에 대한 기록을 남기지 않는다
	//그렇게되면 모든 숫자에 대해 재귀를 허용할 수 있다
	//N과M2를 읽고 보면 쉽게 이해가 될 것이다
	for (int i = 1; i <= N; i++)
	{
		res_arr[cnt] = i;
		recursive_func(cnt + 1);
	}
}

int main(void)
{
	//수열의 범위와 길이값을 입력받는다
	cin >> N >> M;

	//수열 결과를 출력하기 위한 함수 호출
	recursive_func(0);
	return 0;
}