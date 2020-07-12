//유의사항
//브론즈 문제라지만 의외로 많은 생각을 요구하는 문제이다.
//수식으로 풀면 더 간단할 수 있지만
//이분탐색으로 꼭 풀어보길 추천한다.
//이분탐색에 대한 응용법이나 보다 깊이 이해할 수 있게 해주는 문제이다
#include <iostream>     // io
using namespace std;

//달팽이가 오르고(A) 내리고(B) 도달해야하는(V)값의 변수 선언
unsigned long A, B, V;

//달팽이가 총 오른 날짜를 찾기 위한 이분탐색 진행
unsigned long b_search()
{
    unsigned long left = 0, day = 0, right = V + 1;
    unsigned long res = 0;

    while (left <= right)
    {
        //탐색한 날
        day = (left + right) / 2;

        //탐색한 날의 값이 높이보다 크면? res에 현재 날짜를 저장하고
        //다시 루프를 돌아준다
        //루프를 돌다보면 어느 순간 left와 right가 일치하는 날이 생기는데
        //이때가 목표값을 찾은 지점이다
        //루프를 돌리는 이유는 V 와 (day -1) * (A-B) + A 의 값이 항상 같을 수 없고
        //특정 값 ( ex : 5 2 10 ) 일때 V보다 높이 오른 경우가 생길 수 있기 때문이다.
        if (V <= (day - 1) * (A - B) + A)
        {
            right = day - 1;
            res = day;
        }
        //탐색한 날의 값이 높이보다 작으면?
        //탐색 범위를 높여준다
        else
            left = day + 1;
    }
    return res;
}

int main(void)
{
    //달팽이의 움직임과 목표값을 입력받는다
    cin >> A >> B >> V;
    //b_search를 통해 달팽이가 도달한 날을 출력한다.
    cout << b_search() << endl;
    return 0;

}