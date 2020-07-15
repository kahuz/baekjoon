//그래프의 사이클을 구하는 문제
//사이클의 정의를 제대로 알지 못한다면 문제를 보기전 사이클의 정의를 익히고 오자
//문제 풀이는 인접행렬의 DFS 탐색으로 풀이하였다
#include <iostream>	//io
#include <cstring>	//memset
using namespace std;

//순열이 입력될 배열 선언 및 초기화
int input_arr[1001] = { 0 };
//인접행렬 선언ㅇ 및 초기화. 문제의 오름차순 순열은 arr의 인덱스가 되고
//입력된 순열은 arr 인덱스가 가리키는 값이 된다
int arr[1001] = { 0 };
//이미 방문한 노드인지에 대해 확인
bool check[1001] = { 0 };
//입력 테스트 횟수(T)와 순열의 길이(N) 변수 선언 및 초기화
int T = 0, N = 0;
//각 테스트 별 사이클의 총 개수
int circle_num = 0;

//param next_num : 현재의 값이자, 다음 노드를 가리키게 될 인덱스
void find_circle(int next_num)
{
	//현재 노드가 가리키는 다음 노드가 이미 방문한 노드라면
	//사이클 확정
	if (check[next_num])
	{
		circle_num++;
		return;
	}
	//다음 노드에 대한 방문 표시
	check[next_num] = true;

	find_circle(arr[next_num]);

}

int main(void)
{

	//테스트 횟수를 입력받는다
	cin >> T;
	//테스트 회수가 0이되면 루프 종료
	while (T--)
	{
		//순열의 길이를 받아온다
		cin >> N;

		//입력된 순열의 값을 저장
		for (int i = 1; i <= N; i++)
			cin >> input_arr[i];

		//인접행렬 구성
		for (int i = 1; i <= N; i++)
			arr[i] = input_arr[i];

		//순열을 모두 조회하여 사이클 여부를 확인
		for (int i = 1; i <= N; i++)
		{
			//방문하지 않은 노드라면 사이클을 확인하여 사이클을 이루는 노드들에 방문 표시를 한다
			if (check[i] == false)
			{
				check[i] = true;
				find_circle(arr[i]);
			}
		}

		//결과 출력
		cout << circle_num << endl;

		//각 테스트 케이스별로 새로운 방문 기록을 쓰기위해 check배열 초기화
		memset(check, 0, sizeof(check));
		//각 테스트 케이스별로 사이클 값을 쓰기위해 초기화
		circle_num = 0;
	}
	return 0;
}