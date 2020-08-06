//
// 14888 연산자 끼워넣기
//
// 조건
// - N개의 수로 이루어진 수열과 수와 수 사이에 끼워 넣을 수 있는 N-1개의 연산자가 주어진다
// - 연산자는 + , - , * , / 으로만 이루어져있다
// - 수의 순서는 고정되며, 오로지 연산자의 순서만 바뀐다
// - 수열과 연산자가 주어졌을때 만들 수 있는 식의 결과가 최대인 것과 최소인 것을 구하라
// - ** 식의 계산은 연산자의 우선 순위를 무시하고 앞에서부터 진행, 나눗셈은 정수 나눗셈 몫만 취한다 **
// 입력
// - 첫째줄에 수열의 크기 N ( 2<= N <= 11) 이 주어진다
// - 둘째줄에는 수열의 정보가 주어진다
// - 세번째에는 N-1개의 연산자 정보가 주어지는데, 차례대로 덧셈의 개수, 뺄셈의 개수, 곱셈의 개수, 나눗셈의 개수이다
//
// 접근
// - 문제의 가장 중요한 포인트는 식의 계산은 연산자 우선 순위를 무시한다는 점이다.
// - 따라서 입력된 연산자를 모두 벡터에 넣어주고
// - N-1개에 대한 순열의 경우를 모두 구해준뒤 ( 제한시간이 2초, 연산자 순열의 최대 개수는 9개이므로 무리없음 )
// - 순열의 경우에 대해 모든 값을 구하면 해결된다

#include <iostream>		// io
#include <vector>		// vector
using namespace std;

//연산자에 대한 값 정의
#define DEF_PLUS 1
#define DEF_MINUS 2
#define DEF_MUL 3
#define DEF_DIV 4
//수열을 저장할 배열 선언 및 초기화
int numbers[11] = { 0 };
//순열을 위한 check배열 선언 및 초기화
int check[11] = { 0 };
//입력된 연산자를 저장할 벡터 선언
vector<int> operator_v;
//순열의 결과를 저장할 벡터 선언
vector<int> oper_v;
//순열의 크기를 저장할 변수 선언 및 초기화
int N = 0;
//각 연산자의 입력개수를 저장할 변수 선언
int plus_n, minus_n, mul_n, div_n, oper_sum;
//최소 결과값과 최대 결과값을 저장할 변수 선언 및 초기화
int res_min = 9982347592, res_max = -9982347592;

void func(int cnt, int depth)
{
	//입력된 연산자의 총 개수와 동일한 크기의 순열이 구해졌다면
	if (depth > oper_sum)
	{
		//가장 첫번째 값을 먼저 oper_res에 저장
		int oper_res = numbers[0];
		//순열에 저장된 모든 연산결과를 순차적으로 실행한다. 
		//본 문제는 연산자 우선순위를 무시하는 조건임을 기억하자.
		for (int i = 0; i < oper_v.size(); i++)
		{
			int cur_oper = oper_v[i];
			switch (cur_oper)
			{
			case DEF_PLUS:
				oper_res += numbers[i + 1];
				break;
			case DEF_MINUS:
				oper_res -= numbers[i + 1];
				break;
			case DEF_MUL:
				oper_res *= numbers[i + 1];
				break;
			case DEF_DIV:
				oper_res /= numbers[i + 1];
				break;
			}
		}
		//결과값 세팅
		if (res_min > oper_res)
			res_min = oper_res;
		if (res_max < oper_res)
			res_max = oper_res;
	}
	//순열의 경우를 구하는 부분
	for (int i = 0; i < oper_sum; i++)
	{
		//아직 선택하지 않은 연산자라면
		if (check[i] == false)
		{
			//현재 i에 대한 연산자를 가져오고
			int cur_oper = operator_v[i];
			//현재 i에 대한 연산자를 선택 못하게 check[i] = true
			check[i] = true;
			//순열 벡터에 현재 연산자를 저장
			oper_v.push_back(cur_oper);
			func(i + 1, depth + 1);
			//다음 경우르 위해 사용한 순열 값을 반환
			oper_v.pop_back();
			//현재 i에 대한 연산자를 사용했으므로 check[i] = false
			check[i] = false;
		}
	}
}
int main(void)
{
	//수열의 크기를 입력받는다
	cin >> N;
	//수열 값을 입력받는다
	for (int i = 0; i < N; i++)
		cin >> numbers[i];

	// + 연산자에 대한 처리
	cin >> plus_n;
	for (int i = 0; i < plus_n; i++)
		operator_v.push_back(DEF_PLUS);
	// - 연산자에 대한 처리
	cin >> minus_n;
	for (int i = 0; i < minus_n; i++)
		operator_v.push_back(DEF_MINUS);
	// * 연산자에 대한 처리
	cin >> mul_n;
	for (int i = 0; i < mul_n; i++)
		operator_v.push_back(DEF_MUL);
	// / 연산자에 대한 처리
	cin >> div_n;
	for (int i = 0; i < div_n; i++)
		operator_v.push_back(DEF_DIV);
	// 연산자의 총 개수를 저장
	oper_sum = plus_n + minus_n + mul_n + div_n;
	//문제풀이 시작
	func(0, 1);
	//결과 출력
	cout << res_max << "\n" << res_min << endl;
}