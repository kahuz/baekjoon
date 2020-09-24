//
// 문자열 S가 주어졌을때, S의 서로 다르 부분 문자열의 개수를 구하라
//
// 문자열 S를 1 ~ S.size 크기만큼 파싱해가며 set에 넣어 true가 되는 개수를 출력했다
#include <iostream>
#include <string>
#include <set>

using namespace std;

//입력 문자열
string S;
//출력 결과
int res = 0;

int main(void)
{
	//문자열을 입력받는다
	cin >> S;
	//부분 문자열 확인을 위한 set
	set<string> pars;

	//문자열을 1 ~ S.size만큼 나눌 크기를 정한다
	for (int i = 1; i <= S.size(); i++)
	{
		//i만큼 S에 대해 문자열을 나누어 set으로 확인
		for (int j = 0; j <= S.size()-i; j++)
		{
			string tmp = S.substr(j,i);
			bool is_in = pars.insert(tmp).second;
			//중복되지 않은 요소라면 res증가
			if (is_in)
				res++;
		}
	}
	cout << res << endl;
	return 0;
}