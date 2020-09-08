// 18:25
// 조건
// - 네 개의 명령어 D,S,L,R를 이용한 계산기가 있다
// - 계산기에는 레지스터가 하나 있고, 0~10,000 미만의 십진수를 저장 가능하다
// - 각 명령어는 레지스터에 저장된 n을 다음과 같이 변환한다
// - n의 네자릿수를 d1,d2,d3,d4라고 하자
//	-> D : D는 n을 두 배로 바꾼다. (Double)
//		결과 값이 9999보다 큰 경우 10000으로 나눈 나머지를 취한다. D % 10000
//		그 결과 값( 2n mod 10000)을 레지스터에 저장한다
//	-> S : S는 n에서 1을 뺀 결과(n-1)을 레지스터에 저장한다. n이 0이라면 9999가 대신 레지스터에 저장된다
//		S = n-1 == 0 : 9999 ? n-1;
//	-> L : L은 n의 각 자릿수를 왼편으로 회전시켜 그 결과를 레지스터에 저장한다.
//		이 연산이 끝나면 레지스터에 저장된 네 자릿수는 왼편부터 d2,d3,d4,d1
//		L = n shift left
//	-> R : R은 n의 각 자릿수를 오른편으로 회전시켜 그 결과를 레지스터에 젖아한다
//		이 연산이 끝나면 레지스터에 저장된 네 자릿수는 왼편부터 d4,d1,d2,d3
//		R = n shift right
// - 주어진 서로 다르 두 정수 A와 B에 대하여 A를 B로 바꾸는 최소 명령어를 생성하는 프로그램
//
// 입력
// - 첫째줄 : 테스트 횟수 T
// - 1~T+1 줄 : 비교 정수 A와 B
//
#include <iostream>
#include <cmath>
#include <memory.h>
#include <string>
#include <queue>

using namespace std;

bool check[10000] = { 0 };
int A = 0, B = 0, T = 0;

int D_func(int a)
{
	int res_a = a * 2;

	if (res_a > 9999)
		res_a = res_a % 10000;

	return res_a;
}

int S_func(int a)
{
	int res_a = a - 1;

	if (res_a < 0)
		res_a = 9999;

	return res_a;
}

int R_func(int a)
{
	int res_a = a;

	res_a = (a % 10) * 1000 + (a / 10);

	return res_a;
}
int L_func(int a)
{
	int res_a = a;

	res_a = (a % 1000) * 10 + (a / 1000);

	return res_a;
}

string bfs(int a)
{
	queue<pair<int, string>> bfs_q;
	bfs_q.push(make_pair(a, ""));
	check[a] = true;

	while (!bfs_q.empty())
	{
		int x = bfs_q.front().first;
		string oper = bfs_q.front().second;

		bfs_q.pop();

		if (x == B)
		{
			while (!bfs_q.empty())
				bfs_q.pop();
			return oper;
		}
		int nx = D_func(x);

		if (check[nx] == false)
		{
			check[nx] = true;
			bfs_q.push(make_pair(nx, oper + "D"));
		}

		nx = S_func(x);

		if (check[nx] == false)
		{
			check[nx] = true;
			bfs_q.push(make_pair(nx, oper + "S"));
		}

		nx = L_func(x);
		if (check[nx] == false)
		{
			check[nx] = true;
			bfs_q.push(make_pair(nx, oper + "L"));
		}
		nx = R_func(x);

		if (check[nx] == false)
		{
			check[nx] = true;
			bfs_q.push(make_pair(nx, oper + "R"));
		}
	}
}
int main(void)
{
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		memset(check, false, sizeof(check));
		cin >> A >> B;
		string res = bfs(A);
		cout << res << endl;
	}
	return 0;
}