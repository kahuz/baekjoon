//재귀 연습용 문제
//본 문제는 코드를 보는것은 큰 의미가 없으며
//코드를 보기 전 노트를 이용해 숫자의 흐름을 파악하여 구현할 수 있도록 하자
//만약 필기로 모든 과정을 확인하였는데도 구현이 되지 않는다면
//아래 코드를 참고하자
#include <iostream>		//io

using namespace std;

//1~n의 수열 최대값(n)을 입력받을 N과 수열의 길이를 결정할 M 변수 선언 및 초기화
int N = 0, M = 0;
//결과를 출력하기 위한 배열 선언 및 초기화
int res_arr[8] = { 0 };

//param cur_num : 현재 값
//param cnt : 재귀 호출 횟수
void recursive_func(int cur_num, int cnt)
{
	//재귀 호출 횟수가 M만큼 이루어지면 res_arr에 M개의 수가 저장되었으므로
	if (cnt == M)
	{
		//res_arr에 저장된 M개의 수열을 출력
		for (int res_i = 0; res_i < M; res_i++)
			cout << res_arr[res_i] << " ";
		//다음 수열을 위해 개행문자 출력
		cout << "\n";
		return;
	}
	//i는 cur_num 값부터 시작하여
	//재귀 호출 시 다음 값을 가리킬 수 있도록 한다
	//재귀가 호출된 뒤 cnt == M에 의해 호출이 반환되면
	//그 다음 숫자를 매개변수로 전달하여 다음 수열이 출력될 수 있도록 한다
	for (int i = cur_num; i <= N; i++)
	{
		res_arr[cnt] = i;

		recursive_func(i + 1, cnt + 1);
	}
}

int main(void)
{
	//수열의 개수와 수열의 길이를 입력으로 받는다
	cin >> N >> M;

	//수열을 출력할 함수 호출
	recursive_func(1, 0);

	return 0;
}