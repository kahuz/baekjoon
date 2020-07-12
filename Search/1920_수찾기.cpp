//주어진 두 수열( A, B)에 대해
//B에 속한 원소가 A배열에 존재하는지 확인하여야하므로
// 단순 비교로는 O( A  * B )가 될 것이다.
// 주어진 입력값의 범위는 A = 1 ~ 100000, B = 1 ~ 100000 으로 2초 이내에 계산이 불가능
// 값의 범위는 정해져있지만 들어오는 값이 오름차순이 아니기에
// 오름차순 정렬 후 이분탐색을 이용하여 처리
// 정렬은 이전에 활용한 합병정렬을 사용~
// 유의사항, 결과값 출력에 대해 cout >> endl을 사용할 시 시간촤과가 나왔고
//이에 대해 검색한 결과 endl을 '\n'로 변경하여 문제를 해결하였다.
//endl을 출력 버퍼를 비우는 작업을 병행하기 때문에 보다 느린 관계로
//시간제한이 걸린 문제들에 대해서는 개행문자로 처리하도록 하자
#include <iostream>	// io

#define ARR_MMAX 100000
using namespace std;

//입력받을 수열 A와 B이 저장될 변수 선언 및 초기화
int N = 0, M = 0;
//수열 A와 B가 저장될 배열 선언 및 초기화
int n_arr[ARR_MMAX] = { 0 };
int m_arr[ARR_MMAX] = { 0 };

//오름차순 정렬될 배열 선언 및 초기화
int n2_arr[ARR_MMAX] = { 0 };

//분할된 배열에 대한 합병 정렬
//param src ,dst : 분할된 배열의 시작과 끝
void merge(int src, int dst)
{
	//분할된 배열의 중간값 계산
	int mid = (src + dst) / 2;

	//i는 원본 배열의 시작 값으로 초기화
	int i = src;
	//j는 원본 배열의 중간의 다음 값으로 초기화
	int j = mid + 1;
	//k는 복사할 배열의 시작 값으로 초기화
	int k = src;

	//분할된 배열의 시작값(i)가 중간값 까지 증가하며 분할된 배열의 중간 다음 값(j)는 배열의 마지막 까지 증가
	//즉 AB배열 ( ex: 1 2 or ex: 3 4 1 2  ) 에 대해 두개로 분할된 A배열 ( ex: 1 or ex : 3 4 ) 과 B 배열 ( ex : 2 or ex : 1 2 )의
	//A시작 위치 i( ex : 1 or 3 ) 와 B의 시작위치 ( ex : 2 or ex : 1 ) 을 비교하여
	//합병 정렬을 진행
	while (i <= mid && j <= dst)
	{
		//A배열이 오름차순으로 정렬되어 있다면 시작위치 그대로 삽입 시작
		if (n_arr[i] <= n_arr[j])
			n2_arr[k++] = n_arr[i++];
		//A배열이 오름차순으로 정렬되어 있지 않다면, 정렬하여 삽입
		else
			n2_arr[k++] = n_arr[j++];
	}
	//만약 while 루프를 돌고 난 뒤 i값이 mid 값보다 크다면
	//tmp 는 j , 즉 합병될 마지막 위치를 가르키며
	//그렇지 않다면 tmp 는 i, 즉 중간의 다음 위치를 가르킨다
	//이 말은 이미 노드의 왼쪽과 오른쪽이 오름차순으로 정렬되어있는지(true)
	//그렇지 않은지에 대해(false) 확인하는 절차이다
	int tmp = i > mid ? j : i;

	//위 while(i <= mid && j <= dst ) 에서 res_array에 채워지지 못한
	//B시작 위치 ~ 끝 인덱스에 대한 영역에 대해 값을 채운다
	while (k <= dst)
	{
		n2_arr[k++] = n_arr[tmp++];
	}
	//정렬된 값에 대해 원복에 복사, 이후 합병과정에 계속 값을 참조하여야 하기에
	//필요한 과정이다.
	for (int i = src; i <= dst; i++)
	{
		n_arr[i] = n2_arr[i];
	}
}

void merge_sort(int src, int dst)
{
	int mid = 0;

	//src == dst 라면 단 하나의 원소만 남았으므로,
	//나눌 수 있는 상태 ( src < dst )동안 계속 재귀를 호출
	if (src < dst)
	{
		//입력 매개변수 시작과 끝 값을 기준으로 중간 값을 mid에 저장
		mid = (src + dst) / 2;
		//아직 더 나눌 수 있는 상태이므로 현재 참조하고 있는 인덱스를 기준으로
		//반으로 나누어 두번 실행
		merge_sort(src, mid);
		merge_sort(mid + 1, dst);

		//최종적으로 마지막까지 나누었다면 합병을 시작한다
		//재귀의 특성상 가장 마지막 두개의 원소를 가리키는 상태일때
		//처음으로 merge 함수가 실행되는 것을 기억하자
		merge(src, dst);

	}

}

//param left, right : 이분탐색을 위한 범위
//param target : 찾을 값
int binary_search(int left, int right, int target)
{
	//res는 출력될 결과값을 의미, 탐색이 끝나도록 답을 구하지 못한다면 초기값 0이 반환될 것이다
	int res = 0;
	//left, right에 대한 멤버변수 정의
	int arr_left = left;
	int arr_right = right;

	//left값이 right값 이하일때까지만 루프 실행
	//target 값이 배열내의 값들보다 작을 경우 right가 -1까지 가게 되며 ( left > right )
	//배열 내의 값들보다 클 경우 left가 배열 끝값 +1 까지 가게 되므로 ( left > right )
	//while이 무한루프를 돌지 않고 종료된다
	while (arr_left <= arr_right)
	{
		int mid = (arr_left + arr_right) / 2;
		//탐색한 결과가 타겟보다 크면 right 값을 mid 값 -1 을 하여 검색 범위를 left ~ mid-1로 변경한다
		if (n_arr[mid] > target)
			arr_right = mid - 1;
		//탐색한 결과가 타겟보다 작으면 left값을 mid 값 +1 을 하여 검색 범위를 mid + 1 ~ right로 변경한다
		else if (n_arr[mid] < target)
			arr_left = mid + 1;
		else
		{
			//n_arr[mid] == target 이므로 값이 존재한다고 판정, 1을 리턴
			res = 1;
			break;
		}
	}
	//만약 while 루프가 끝날때까지 값 변화가 없다면 ( 값을 찾지 못했다면 )
	// res는 0인체 반환
	return res;

}
int main(void)
{
	//시간제한이 빠듯하기에 입출력 가속을 위해 추가
	std::ios_base::sync_with_stdio(false);
	//탐색할 A배열의 크기를 입력받는다
	cin >> N;
	//탐색할 배열의 값을 입력한다
	for (int i = 0; i < N; i++)
		cin >> n_arr[i];

	//탐색 목표 값을 가질 B배열의 크기를 입력받는다
	cin >> M;
	//목표 값들을 배열에 입력한다
	for (int j = 0; j < M; j++)
		cin >> m_arr[j];
	// 이분 탐색을 위해 오름차순 정렬 진행
	merge_sort(0, N - 1);

	//B배열에 대한 결과를 출력
	for (int k = 0; k < M; k++)
	{
		cout << binary_search(0, N, m_arr[k]) << '\n';
	}
	return 0;
}