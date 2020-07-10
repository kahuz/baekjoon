//유의사항
//해당 문제의 주어지는 입력 크기를 잘 확인하자
//무턱대고 정렬한다면 시간초과가 뜰 것이다
//아래 코드는 합병정렬을 이용하여 답을 구하였다
#include <iostream>		//io

using namespace std;

//입력받을 배열 A(N) B(M)의 크기 선언 및 초기화
int N = 0, M = 0;

//입력 값을 받을 배열
int* input_array;
//최종결과 배열
int* res_array;

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
		if (input_array[i] <= input_array[j])
			res_array[k++] = input_array[i++];
		//A배열이 오름차순으로 정렬되어 있지 않다면, 정렬하여 삽입
		else
			res_array[k++] = input_array[j++];
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
		res_array[k++] = input_array[tmp++];
	}
	//정렬된 값에 대해 원복에 복사, 이후 합병과정에 계속 값을 참조하여야 하기에
	//필요한 과정이다.
	for (int i = src; i <= dst; i++)
	{
		input_array[i] = res_array[i];
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
int main(void)
{
	//시간제한이 빠듯하기에 입출력 가속을 위해 추가
	std::ios_base::sync_with_stdio(false);
	//두 배열의 크기 N과 M을 받아온다
	cin >> N >> M;

	int arr_legnth = N + M;
	input_array = new int[arr_legnth];
	res_array = new int[arr_legnth];

	for (int i = 0; i < arr_legnth; i++)
	{
		cin >> input_array[i];
	}

	//합병 정렬을 할 배열의 시작 인덱스와 끝 인덱스를 전달
	merge_sort(0, arr_legnth - 1);

	for (int i = 0; i < arr_legnth; i++)
	{
		cout << res_array[i] << " ";
	}
	cout << endl;
	return 0;
}