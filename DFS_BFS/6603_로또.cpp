#include <iostream>	// io

using namespace std;

//조합을 이룰 로또의 개수
#define LOTTO_NUM 6
//로또를 이루는 집합의 원소 개수 선언 및 초기화
int N = 0;
//로또 집합의 원소가 저장될 배열 선언 및 초기화
int lotto[49] = { 0, };
//결과 출력을 위한 배열 선언 및 초기화
int output[LOTTO_NUM] = { 0, };

//param cur_num : 현재 가르키고 있는 로또 번호
//param depth : 재귀의 깊이, 스택에 쌓인 크기
void dfs(int cur_num, int depth)
{
	//depth 가 로또 총 개수에 도달하면
	if (depth == LOTTO_NUM)
	{
		//앞서 쌓아둔 로또 번호를 모두 출력
		for (int i = 0; i < LOTTO_NUM; i++)
		{
			cout << output[i] << " ";
		}
		cout << endl;

		return;
	}

	//현재 번호부터 최대 로또 번호까지 탐색
	for (int i = cur_num; i < N; i++)
	{
		//출력 배열의 현재 depth 위치에 탐색한 로또 번호를 삽입
		output[depth] = lotto[i];
		//LOTTO_NUM 만큼 쌓일때까지 재귀로 들어간다
		dfs(i + 1, depth + 1);
		//재귀가 끝나면 다음 로또 번호를 조회해 현재 depth 위치에 번호를 교환해준다
	}
}
int main(void)
{

	while (true)
	{
		//로또를 이룰 집합 원소의 개수 N을 받아온다
		cin >> N;

		//입력값에 0이 들어오면 테스트를 종료한다
		if (N == 0)
		{
			;
			break;
		}
		else
		{
			for (int i = 0; i < N; i++)
				cin >> lotto[i];
		}
		//입력된 로또번호의 시작 위치와 시작 뎁스의 값을 매개변수로 dfs함수 호출
		dfs(0, 0);
		cout << endl;
	}

	return 0;
}