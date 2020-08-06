// 시작 7:10 로직 설계 7:20
// 14889 - 스타트와 링크 
//
// 조건
// - 총 N명의 사람이 모여 축구를 하려한다. 
// - N명은 짝수이며 N/2명으로 이루어진 스타트팀과 링크 팀으로 사람을 나누려한다.
// - 참여자는 각자 1~N번까지 번호가 부여되며, 번호의 쌍마다 팀에 더해지는 능력치가 존재한다.
//	-> 백준 문제 참고
// - 팀의 능력치는 팀에 속한 모든 쌍의 능력치의 합이다. 
// - 입력으로 주어지는 선수별 능력치를 가지고 두 팀의 능력치 총합의 차이가 최소일 때의 값을 출력하라
//
// 입력
// - 첫째줄 : 선수 N ( 4<= N <= 20 ) 이 주어진다
// - 2~N+1줄 : 각 번호별 타 선수와의 능력치 값이 주어진다.
//
// 접근
// - 주어지는 입력값을 인접행렬로 구성한다
// - 조합을 이용하여 한 팀의 선수 명단을 구하여 TEAM_S를 구성하고, 남은 선수는 TEAM_L로 넘겨 주는 모든 경우를 구한다
// - 모든 경우의 수에 대해 능력치 차이값을 구한 뒤 결과값을 최소값으로 갱신하여 출력
//
#include <iostream>	//io
#include <cmath>	//abs

using namespace std;

//선수들의 연결관계에 따른 능력치를 저장할 배열 선언 및 초기화
int player_arr[20][20] = { 0 };
//선수 선별을 위한 배열 선언 및 초기화
int player[20] = { 0 };
//선수 숫자 변수 선언 및 초기화
int N = 0;
//결과를 위한 변수 선언 및 초기화
int res = 997249;

void func(int cnt, int depth)
{
	//선별한 선수가 N/2만큼 선별되었다면
	// 즉, 팀 하나가 구성이 되었다면
	if (depth >= (N / 2))
	{
		int index = 0;
		int team_s = 0;
		int team_l = 0;

		//team_s와 team_l에 대해 모든 선수명단 탐색
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				//player배열을 통해 true라면 team_s로 분류된 상태이며
				//만약 i선수가 team_s라면 j루프에 대해 team_s의 경우만 모두 확인
				//( i에 대한 연결관계를 확인하기 때문이다 )
				if (player[i] && player[j]) {
					team_s += player_arr[i][j];
					team_s += player_arr[j][i];
				}
				//false라면 team_l로 분류된 상태
				else if (!player[i] && !player[j]) {
					team_l += player_arr[i][j];
					team_l += player_arr[j][i];
				}
			}
		}
		//결과에 대해 가장 낮은 값으로 갱신
		if (res > abs(team_s - team_l))
			res = abs(team_s - team_l);
		return;
	}
	//조합을 통해 하나의 팀을 구성시킨다
	//여기서는 team_s로 생각하여 코드작성 중
	for (int i = cnt; i < N; i++)
	{
		if (player[i] == false)
		{
			player[i] = true;
			func(i + 1, depth + 1);
			player[i] = false;
		}
	}
}

int main(void)
{
	//선수 숫자를 입력받는다
	cin >> N;
	//선수들의 연결관계에 따른 능력치를 입력받는다
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> player_arr[y][x];
		}
	}
	//풀이 함수 실행
	func(0, 0);
	//결과 출력
	cout << res << endl;
	return 0;
}