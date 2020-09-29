//
// 크기가 3x3인 배열 A가 있다. 1초가 지날때마다 배열에 연산이 적용된다
// R연산 : 배열 A의 모든 행에 대해서 정렬을 수행. 행의 개수 >= 열의 개수인 경우 적용
// C연산 : 배열 A의 모든 열에 대해서 정렬을 수행. 행의 개수 < 열의 개수인 경우 적용

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
//연산 정보가 저장될 배열 선언
int map[101][101] = { 0 };
//초기 정렬 결과 r,c max값. 초기 3
int r = 3, c = 3;
//답을 도출할 r,c,k
int R = 0, C = 0, K = 0;

void C_oper()
{
	//R연산 결과로 나온 최대 열의 인덱스까지 탐색 정렬
	for (int c_idx = 1; c_idx <= c; c_idx++)
	{
		//C연산 결과로 나온 값의 호출 횟수, 값 에 대한 배열 선언
		vector<pair<int, int>> value_v;
		//C연산 결과로 나온 값에 대한 호출 횟수를 저장할 배열
		int value[101] = { 0 };
		//해당 열의 최대 값
		int max_value = 0;
		//해당 열의 행들을 참조하기 위한 변수
		int r_idx = 1;

		//최대 r값까지 탐색
		while (r_idx <= r)
		{
			//최대값 갱신
			if (max_value < map[r_idx][c_idx])
				max_value = map[r_idx][c_idx];
			//map[r_idx][c_idx]로 나온 값에 대해 value 배열의 값을 증가시켜 횟수를 기록
			value[map[r_idx][c_idx]]++;
			//횟수 기록 후 0으로 초기화 작업
			map[r_idx][c_idx] = 0;
			//다음 탐색을 위해 r_idx를 증가시켜준다
			r_idx++;
		}
		//탐색 결과에 대해 1~최대값까지 탐색
		for (int i = 1; i <= max_value; i++)
		{
			//value[i], 즉 값(i)에 대해 호출 횟수가 0회 이상인 경우 value_v에 저장
			//호출횟수, 값 으로 저장
			if (value[i] > 0)
				value_v.push_back(make_pair(value[i], i));
		}
		//value_v는 값에 대해 정렬되어 있는 상태이며,
		//다시 호출 횟수로 재정렬해주면 호출횟수가 높은 순이자 값이 오름차순으로 저장된 상태로 정렬된다
		sort(value_v.begin(), value_v.end());
		//map에 값을 재설정하기 위한 idx값 선언
		int idx = 1;
		//map값 재설정 부분
		//호출횟수, 해당 값 을 순서대로 저장해준다
		for (int j = 0; j < value_v.size(); j++)
		{
			map[idx++][c_idx] = value_v[j].second;
			map[idx++][c_idx] = value_v[j].first;
		}
		//최대 r값을 확인하기 위해 idx--를 한번해준다
		idx--;
		//최대 r값 갱신
		if (r < idx)
			r = idx;

	}
}
//C_oper와 같은 방식으로 동작됨
void R_oper()
{
	for (int r_idx = 1; r_idx <= r; r_idx++)
	{
		vector<pair<int, int>> value_v;
		int value[101] = { 0 };
		int max_value = 0;
		int c_idx = 1;

		while (c_idx <= c)
		{
			if (max_value < map[r_idx][c_idx])
				max_value = map[r_idx][c_idx];

			value[map[r_idx][c_idx]]++;
			map[r_idx][c_idx] = 0;
			c_idx++;
		}

		for (int i = 1; i <= max_value; i++)
		{
			if(value[i] > 0)
				value_v.push_back(make_pair(value[i], i));
		}
		sort(value_v.begin(), value_v.end());

		int idx = 1;
		
		for (int j = 0; j < value_v.size(); j++)
		{
			map[r_idx][idx++] = value_v[j].second;
			map[r_idx][idx++] = value_v[j].first;
		}
		idx--;

		if (c < idx)
			c = idx;

	}
}
//정렬 연산을 위한 함수
//return : 정렬 횟수
int solution()
{
	int res = 0;
	//map[R][C] == K거나 res > 100 일때까지 연산
	while (true)
	{
		if (map[R][C] == K)
		{
			return res;
		}
		else if (res > 100)
			return -1;
		
		if (r >= c)
			R_oper();
		else
			C_oper();

		res++;
	}
}
int main(void)
{
	//R,C,K에 대한 입력을 받아옴
	cin >> R >> C >> K;
	//초기 map값을 받아옴. R,C 가 1<= R,C <=100 이므로 인덱스를 1부터 처리.
	for (int r = 1; r <= 3; r++)
	{
		for (int c = 1; c <= 3; c++)
		{
			cin >> map[r][c];
		}
	}
	//연산 수행 및 결과 출력
	cout << solution() << endl;

	return 0;
}