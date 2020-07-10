//유의할 점
//문제의 제한 시간과 주어지는 테스트 케이스의 수를 잘 확인해보자
//시간복잡도를 계산해보고 문제를 풀 수 있도록 한다.
#include <iostream>	//io

using namespace std;

int N = 0; //초기 쿠폰 수
int K = 0; //치킨을 교환하기 위한 쿠폰의 수
int order_sum = 0; //테스트 케이스 별 총 주문 수

//param cur_coupon : 현재 가지고 있는 쿠폰의 수
void chicken_order(int cur_coupon)
{
	//쿠폰을 모두 소진했을 경우 함수를 종료한다
	if (cur_coupon == 0)
		return;
	//현재 쿠폰이 쿠폰으로 변환 가능한 도장의 수보다 많을 경우
	if (cur_coupon >= K)
	{
		//쿠폰으로 변환 가능한 주문수를 먼저 구한뒤
		int cur_order = (cur_coupon / K) * K;
		//주문한 수량만큼 총 주문수량에 더해주고
		order_sum += cur_order;
		//현재 주문수로 변환 가능한 쿠폰을 더해 준 뒤
		cur_coupon += (cur_coupon / K);
		//주문한 수만큼 쿠폰을 소모시킨다
		cur_coupon -= cur_order;
	}
	else
	{
		//남은 쿠폰만큼 모두 주문을 해준 뒤
		order_sum += cur_coupon;
		//쿠폰을 소모한다
		cur_coupon = 0;
	}
	//현재 쿠폰 정보를 토대로 재귀함수를 호출
	chicken_order(cur_coupon);
}
int main(void)
{
	//두번의 입력(N과 K)가 있을때까지 루프
	while (cin >> N >> K)
	{
		order_sum = 0;
		//초기 쿠폰값을 매개변수로 chicken_order 함수를 호출한다
		chicken_order(N);
		//chicken_order함수를 통해 구한 주문 수량을 출력
		cout << order_sum << endl;
	}
	return 0;
}