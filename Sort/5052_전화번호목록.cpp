//
// 주어진 전화번호 목록에 대해 일관성을 파악하는 문제
// 일관성이 있다는 것은 한 번호가 다른 번호의 접두어인 경우가 없다는 의미이다. 끄덕.
//
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

//전화번호 목록을 저장할 배열
vector<string> nums_v;
//테케 횟수
int T = 0;

int main(void)
{
	//테케 횟수를 입력받는다
	cin >> T;

	//테스트 케이스만큼 while
	while (T--) 
	{
		//일관성 여부를 확인할 변수
		bool is_ok = true;
		//전화번호 목록과 전화번호 길이에 대한 변수
		int n = 0, cur = 0, next = 0;
		//전화번호 목록 개수를 입력받는다
		cin >> n;

		//전화번호 목록을 입력받는다
		for (int i = 0; i < n; i++) 
		{
			string input;
			cin >> input;
			nums_v.push_back(input);
		}

		//입력받은 전화번호에 대해 정렬
		sort(nums_v.begin(), nums_v.end());
		//정렬된 전화번호 목록에 대해 탐색
		for (int i = 0; i < n - 1; ++i) 
		{
			cur = nums_v[i].length();
			next = nums_v[i + 1].length();
			//현재 전화번호가 다음 번호에 포함되는지 확인
			if (nums_v[i + 1].substr(0, cur) == nums_v[i]) {
				cout << "NO" << endl;
				is_ok = false;
				break;
			}
		}
		//접두어인 경우가 없다면 yes 출력
		if (is_ok) 
			cout << "YES" << endl;
		//사용한 벡터 초기화
		nums_v.clear();
	}

	return 0;
}