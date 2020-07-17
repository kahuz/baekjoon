//백트래킹의 대표적인 문제
//퀸의 위치를 정하기 위한 제한 조건을 어떻게 주냐에 따라 구현 난이도가 달라진다
#include <iostream>     //  io

using namespace std;
//체스판의 크기이자 퀸의 개수 변수 선언 및 초기화
int N = 0;
//결과값을 저장할 변수 선언 및 초기화
int res = 0;
//행을 기준으로 본 ( 열로 생각해도 상관이 없다 ) , 배열 선언 및 초기화
//row[i]에서 i는 행번호를, i의 원소는 열번호를 뜻한다
int row[15];

//param row_index : 현재 퀸이 위치한 행 번호
bool is_there(int row_index)
{
    //row는 1부터 증가되어오고 있으므로
    //현재 row 값 이전에 배치된 퀸의 위치를 확인하는 작업
    for (int i = 0; i < row_index; i++)
    {
        //이전에 i행에 배치된 퀸의 열과 현재 row_index 행에 있는 퀸의 열이 같다면
        //서로 공격되는 상황이므로 배치할 수 없음
        if (row[row_index] == row[i])
            return true;
        //현재 row(row_index)보다 낮은 이전 row(i) 행의 x,y 증감 값을 이용해 같은 대각선에 있는지 확인
        if (row_index - i == abs(row[row_index] - row[i]))
            return true;
    }
    //위 조건들이 모두 부합되면, 현재 위치에 퀸을 놓을 수 있다
    return false;
}

//param row_index : 현재 퀸이 위치한 행 번호
void dfs(int row_index) {
    //row(행,y)의 위치를 증가시켜가며 퀸이 N개의 배치가 완료되었을때
    if (row_index == N)
    {
        //res값을 증가
        res++;
    }
    else
    {
        //현재 row_i(행,y)의 위치에서 column(열,x)의 위치만 바꿔가며 퀸 배치가 가능한지 확인
        for (int j = 0; j < N; j++)
        {
            row[row_index] = j;
            //배치가 가능하면 
            if (!is_there(row_index))
            {
                //다음 행에 대해서도 확인
                dfs(row_index + 1);
            }
        }
    }
}

int main(void)
{
    //체스판의 크기이자 퀸의 개수를 입력받는다
    cin >> N;

    //퀸 배치를 위한 dfs 탐색 시작
    dfs(0);

    //결과값 출력
    cout << res << " ";

    return 0;
}
