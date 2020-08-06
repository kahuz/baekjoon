// 시작 9:15, 로직 설계 9:30
// 17471 게리맨더링
//
// "문제가 어렵다면 14889 스타트와 링크를 먼저 풀어보자"
//
// 조건
// - N개의 구역이 1~N번호가 붙여져있으며, 두개의 선거구로 나누려한다
// - "각 구역은 두개의 선거구 중 하나에 포함되어야한다" <- 포인트
// - 선거구는 구역을 "적어도 하나"를 포함해야한다, 즉 무조건 두개의 선거구로 나뉘어져야함
// - 한 선거구에 포함된 구역은 모두 연결되어야한다
// - 두 선거구의 인구 차이를 최소화 했을때의 값을 구하라
// - "시간제한 0.5초"
// 입력
// - 첫째줄 : 구역의 개수 N ( 2<= N <= 10)
// - 두번째줄 : 각 구역별 인구수 정보
// - 3~N+2줄 : 첫번째값은 인접한 구역 수, 나머지는 인접한 구역의 번호
//
// 접근
// - 인접행렬을 이용해 각 구역의 연결 정보를 입력받는다
// - 구역에 대해 연결관계에 대한 모든 조합을 구하고, 나머지 영역과 인구 차이를 확인한다
//		-> 이때 선별된 각 선거구의 모든 구역이 연결되어있지 않다면 인구차이를 구하지 않고 다음으로 넘긴다
//
#include <iostream>		// io
#include <vector>		// vector
#include <cmath>		// abs
#include <queue>		// queue

//결과에 대한 초기값을 정의
#define INIT_RES 99875938
using namespace std;

//구역별 인구수 정보를 닮을 배열 선언 및 초기화
int people[11] = { 0 };
//조합으로 선택한 구역이 담길 배열 선언 및 초기화
int Select[11] = { 0 };
//구역간의 연결관계를 나타낼 배열 선언 및 초기화
int connect_area[11][11] = { 0 };
//입력 구역의 개수와 결과값 선언 및 초기화
int N = 0, res = INIT_RES;

bool check_connect(vector<int> area, bool area_type)
{
	//탐색에 대한 방문처리 배열 선언 및 초기화
	bool visited[11] = { 0 };
	//연결요소를 확인할 q 선언
	queue<int> q;
	//입력 구역에 대한 첫번째 구역을 q에 삽입하여 탐색할 수 있도록 한다
	q.push(area[0]);
	//첫번째 구역에 대해 방문 표시
	visited[area[0]] = true;
	//연결된 구역의 총 개수를 확인할 cnt 변수 선언 및 초기화
	int Cnt = 1;
	//모든 탐색이 완료될때까지 루프
	while (!q.empty())
	{
		//현재 탐색 구역을 가져온다
		int cur_area = q.front();
		//가져온 노드는 반환
		q.pop();
		//1~N 구역에 대해 탐색
		for (int i = 1; i <= N; i++)
		{
			//현재 구역과 i가 연결되어 있으며, i가 area에 포함되어있고, 방문하지 않았다면
			//ex ) 1 -> 2 -> 3 -> 4 에 대해 확인한다면
			// cur_area가 1일때 i를 증가시키며 1과 연결된 다음 노드를 찾고 ( 2를 찾고 )
			// 그 2가 현재 선거구에 포함되어있는지 확인해준 뒤
			// 2를 queue에 넣어 2에 연결된 다음 노드를 찾는 형태이다
			// 즉, Select에 1 , 2, 4 가 true라면
			// 1 ok -> 2 ok -> 3 no, is not include to select array -> 4 ok
			// 로 진행되기에 cnt는 3이 될 것이고 area size 또한 3이기에 모두 연결되어있다는 것을 알 수 있다.
			if (connect_area[cur_area][i] == true && Select[i] == area_type && visited[i] == false)
			{
				//방문표시를 해주고
				visited[i] = true;
				//area에 속한 i가 연결되어있으므로 cnt 증가
				Cnt++;
				//다음 탐색 시작
				q.push(i);
			}
		}
	}

	/* 2번 조건에 위배 되지 않는다 = BFS에서 Count한 값과 Vector의 Size가 같다. */
	if (area.size() == Cnt) return true;
	return false;
}

void diff_area()
{
	//선거구 A와 선거구 B에 대한 벡터 선언
	vector<int> area_A, area_B;
	//선거구 A와 선거구 B의 인구수를 저장할 변수와, 그 차이값을 저장할 변수 선언 및 초기화
	int a_people = 0, b_people = 0, diff_val = 0;

	//1~N구역에 대해 어느 선거구에 해당하는지 확인
	for (int i = 1; i <= N; i++)
	{
		//선거구 A 라면
		if (Select[i] == true)
		{
			area_A.push_back(i);
			a_people += people[i];
		}
		//선거구 B 라면
		else
		{
			area_B.push_back(i);
			b_people += people[i];
		}
	}
	//divide_area에서 Select[area_num] == true, 즉 선거구 A를 기준으로 조합을 구하였으므로,
	//선거구 A는 최소 하나이상의 구역을 포함하고 있지만
	//선거구 A가 최대 N개의 구역을 가질 수 있으므로, 선거구 B가 하나도 선택되지 않은 상태에 대해서는 return해야함
	if (area_B.size() == 0) return;

	//조합으로 선별한 선거구 A가 모두 연결되어 있는지 확인
	if (!check_connect(area_A, true))
		return;
	//조합으로 선별한 선거구 B가 모두 연결되어 있는지 확인
	if (!check_connect(area_B, false))
		return;

	//area_A, area_B 모두 연결되어 있다면 두 선거구의 인구차를 diff_val에 저장
	diff_val = abs(a_people - b_people);
	//이전 res값보다 현재 diff_val이 더 작다면 res의 값을 갱신한다.
	if (res > diff_val)
		res = diff_val;

}
// param idx : 조합으로 선택하기 위한 후보군의 시작 위치
// param depth : 조합으로 선택된 개수
void divide_area(int idx, int depth)
{
	//구역A ( Select[area_num] == true ) 에 대해 하나이상 선택되었다면
	if (depth >= 1)
	{
		//두 영역에 대해 인구수 차이를 확인한다
		diff_area();
		//return이 없는 이유는 조합이 1개~N개에 대해 모두 검토해봐야하기때문
	}

	//모든 조합식을 찾는다
	for (int j = idx; j <= N; j++)
	{
		if (Select[j] == false)
		{
			Select[j] = true;
			divide_area(j, depth + 1);
			Select[j] = false;
		}
	}

}

int main(void)
{
	cin >> N;
	//구역의 인구수 정보를 입력받는다
	for (int i = 1; i <= N; i++)
		cin >> people[i];
	//구역의 연결관계를 입력받는다
	for (int cur_area = 1; cur_area <= N; cur_area++)
	{
		int connect_num;
		cin >> connect_num;

		for (int j = 0; j < connect_num; j++)
		{
			int other_area;
			cin >> other_area;
			connect_area[cur_area][other_area] = true;
		}
	}
	//문제풀이 실행
	divide_area(1, 0);

	if (res == INIT_RES)
		cout << -1 << endl;
	else
		cout << res << endl;
	return 0;
}