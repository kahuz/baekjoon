//
// 조건
// - 문자열 S와 단어목록 A가 주어진다
// - A에 포함된 문자열을 하나이상 공백없이 붙여서 S를 만들 수 있는지 없는지 구하라
// - A에 포함된 단어는 여러번 사용할 수 있다
//
// 입력
// 첫째줄 : 길이 100이하인 S가 주어진다
// 둘째줄 : A에 포함된 단어의 개수가 주어진다 ( 1 <= A.num <= 100 )
// 나머지 : A에 포함된 단어가 주어진다
//
// 조합으로 접근하려하였지만 단어목록개수가 최대 100이므로 시간초과로 불가능함을 인지,
// DP접근법을 몰라서 질문게시판 https://www.acmicpc.net/board/view/45056 를 참고, 코드 분석을 하였습니다.
//
#include <iostream>
#include <vector>
#include <string>
#include <memory.h>
using namespace std;

//비교할 문자열 s
string s;
//단어목록 개수 n
int n;
//단어목록을 저장할 벡터
vector<string> a;
// dp에서 cache 역할을 할 배열
//
int dp[105];

//param pos : 문자열 s와 a의 단어목록 [i번째]를 비교한 뒤 a[i]가 포함된 상태일 경우
//			a[i]의 와 비교를 끝낸 s의 위치값, (ex : s "abcedf" a[i] "abc" 일때, 처음 pos는 0 이고, a[i]가 s의 3번째까지 일치하므로
//			다음 pos 값은 4를 넘겨주어 edf를 비교할 수 있도록 넘겨준다
//return : 문자열 생성 가능 여부 true/false
int solve(int pos) {
	//재귀를 타고 오다 pos가 s.size값과 동일하면 결과적으로 0~s.size까지 일치한 단어를 선택해왔기에 (a의 단어들로 s를 만들 수 있는 상태가 됨 ) true가 된다
	if (pos == s.size()) return true;

	//탐색 위치 pos에 대해 탐색 완료를 하여 true가 되어있다면 더이상 탐색하지 않고 return을 하는 부분으로 생각됨
	int& ret = dp[pos];
	if (ret != -1) return ret;
	ret = 0;
	//단어목록 a에 대해 모든 단어들을 탐색
	for (int i = 0; i < n; ++i) {
		//탐색 위치의 단어의 길이를 len에 저장
		int len = a[i].size();
		//비교 문자열 s로부터 비교완료한 현재 위치 pos를 뺀 값이 탐색단어 a[i]보다 크면 비교 문자열 s를 만족할 수 없으므로 continue
		if (s.size() - pos < len) continue;
		//비교 문자열 s를 만들 수 있는 a[i]가 현재 위치 pos ~ len까지의 값과 탐색단어 a[i]와 같다면 문자열 s를 이룰 수 있으므로
		//다음 탐색을 시도하도록 재귀호출
		//i = 0 부터 계속 탐색하는 이유는 단어목록 a에서 중복된 단어를 선택할 수 있으므로 모든 단어를 계속 확인해주어야함
		if (s.substr(pos, len) == a[i]) {
			//재귀호출의 끝이 true 혹은 ret= 0 으로 끝나는지에 대한 값을 받는 부분으로 생각됨
			ret = ret || solve(pos + len);
		}
	}

	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("in.txt", "r", stdin);
	cin >> s >> n;
	a.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	memset(dp, -1, sizeof(dp));
	cout << solve(0) << '\n';
	return 0;
}