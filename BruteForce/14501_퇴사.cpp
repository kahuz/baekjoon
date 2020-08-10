//
// 14501 퇴사
//
// 조건
// - 오늘부터 N+1일째 퇴사를 할 것이다.  
// - 퇴사 전에 상담을 통해 최대한 많은 페이를 벌려고 한다
// - 각 날짜마다 상담 기간과 상담 금액이 제공되고 상담기간은 1일보다 클 수 있다
// - 이때, N+1일동안 상담을 통해 얻을 수 있는 가장 큰 금액을 출력하라
//
// 입력
// - 첫째줄 : 상담기간 N ( 1<= N <= 15 )
// - 2~N+1줄 : 상담기간 T와 상담금액 P가 주어진다
//
// 접근
// - 1~N일동안 잡힌 상담에 대해 만들어낼 수 있는 모든 조합을 출력한다
// - 단, 조합을 할때 idx를 상담기간만큼 증가하게하여 접근 가능한 모든 수 찾는다
//
/*
#include <iostream>
#include <vector>

using namespace std;
//상담 일정을 저장할 벡터 선언
vector<pair<int, int>> advice_v[15];
//입력 값을 받을 변수 선언 및 초기화
int N = 0, T = 0, P = 0;
//결과 값을 저장할 변수 선언 및 초기화
int res = 0;

//param idx : 이전 상담일 + 상담기간의 값
//param pay_sum : 상담한 내역에 대한 총 금액
void func(int idx, int pay_sum)
{
	//만약 상담해야하는 기간이 퇴사일을 넘어가면 return
	if (idx > N)
		return;
	//상담 기간이 퇴사일과 동일하다면
	else if (idx == N)
	{
		//pay_sum이 res보다 클때 res에 반영하고
		if (res < pay_sum)
			res = pay_sum;
		//더 탐색할 필요 없이 리턴
		return;
	}
	//상담기간이 퇴사일 전이라면
	else
	{
		//우선 현재까지의 pay_sum이 res보다 큰지 확인하고 반영을 결정
		if (res < pay_sum)
			res = pay_sum;
	}
	// i 는 상담 일정의 날짜를 의미, 퇴사일 전까지 탐색
	for (int i = idx; i < N; i++)
	{
		//현재 날짜 + 상담 기간으로 다음 idx를 결정
		int n_idx = i + advice_v[i].front().first;
		//상담에 대한 보상금을 입력받고
		int n_pay = advice_v[i].front().second;
		//다음 실행
		func(n_idx, pay_sum + n_pay);
	}
}

int main(void)
{
	//퇴사 기간을 입력받는다
	cin >> N;
	//퇴사전날까지의 상담 일정을 받는다
	for (int i = 0; i < N; i++)
	{
		cin >> T >> P;
		advice_v[i].push_back(make_pair(T, P));
	}
	//풀이 실행
	func(0, 0);
	//결과 출력
	cout << res << endl;
	return 0;
}
*/