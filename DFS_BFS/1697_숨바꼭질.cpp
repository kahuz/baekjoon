// 유의 사항
// 출력 결과를 쉽게 저장하기 위해 queue를 <int cur_pos,int move_num>형태로 선언하였다.
// stl에서 큐의 크기가 정확히 얼마인지 알 수 없지만 그로인해 메모리 초과 오류가 발생
// 생각해보니 check 배열에 방문과 동시에 내가 이동한 횟수를 기록하는 방법으로 메모리 최적화가 가능하다는 것을 깨닫고 적용하여 해결
// 코드 주석은 queue를 <int,int> 형태로 선언했을 때의 실수를 기억할 수 있도록 코드를 남겨두도록 하였다.
#include <iostream>	//io
#include <queue>	//queue
#include <cstring>	//memset
using namespace std;

//움직일 수 있는 최대 범위 값 선언
#define RANGE 100001

//수빈이(N)와 동생(K)의 위치 변수 선언 및 초기화
int N = 0, K = 0;

//수빈이의 위치를 기록하기 위한 배열 선언 및 초기화
int check[RANGE] = { 0 };

//bfs 탐색을 위한 큐 선언
//queue<pair<int, int>> bfs_q;
queue<int> bfs_q;

int bfs(int soobin_pos, int brother_pos)
{
	//수빈이의 위치를 탐색 시작 위치로 삽입한다.
	//bfs_q.push(make_pair(soobin_pos, 0));
	bfs_q.push(soobin_pos);
	//탐색 시작 위치에 대해 방문하였음을 표기한다.
	//check[soobin_pos] = true;
	check[soobin_pos] = 1;

	while (!bfs_q.empty())
	{
		//탐색 노드에 대한 위치와 현재 위치까지 움직인 회수를 가져온다.
		//int cur_pos = bfs_q.front().first;
		//int move = bfs_q.front().second;
		int cur_pos = bfs_q.front();
		int move = check[cur_pos];
		
		//탐색 노드의 값을 가져왔으므로 노드를 반환
		bfs_q.pop();

		//가져온 현재 위치가 동생의 위치와 같을 경우 move - 1 값을 반환한다.
		//move -1인 이유는 if문의 처리를 쉽게 하고자 방문하지 않을 지역을 0, 방문한 지역은 움직인 횟수 +1로 기록하였기 때문
		if (cur_pos == brother_pos)
			return move - 1;
		else
		{
			//움직일 수 있는 3가지 방법에 대해 for문과 switch 문으로 작성
			for (int i = 0; i < 3; i++)
			{
				//다음 탐색지에 대한 변수 선언 및 초기화
				int next_pos = 0;

				//i = 0 일때는 x-1, i = 1 일때는 x+1, i = 2 일때는 x*2로 이동
				switch (i)
				{
					//move cur_pos -1
				case 0:
					next_pos = cur_pos - 1;
					if (next_pos >= 0 && next_pos < RANGE)
					{
						//다음 행선지가 방문하지 않았다면
						//if (!check[next_pos])
						if (check[next_pos] == 0)
						{
							//다음 행선지를 기록하고 check 배열에 움직임의 횟수를 저장
							//bfs_q.push(make_pair(next_pos, move + 1));
							bfs_q.push(next_pos);
							check[next_pos] = check[cur_pos] + 1;
						}
					}
					break;
					//move cur_pos +1
				case 1:
					next_pos = cur_pos + 1;

					if (next_pos >= 0 && next_pos < RANGE)
					{
						//다음 행선지가 방문하지 않았다면
						//if (!check[next_pos])
						if (check[next_pos] == 0)
						{
							//다음 행선지를 기록하고 check 배열에 움직임의 횟수를 저장
							//bfs_q.push(make_pair(next_pos, move + 1));
							bfs_q.push(next_pos);
							check[next_pos] = check[cur_pos] + 1;
						}
					}
					break;
					// move cur_pos *2
				case 2:
					next_pos = cur_pos * 2;

					if (next_pos >= 0 && next_pos < RANGE)
					{
						//다음 행선지가 방문하지 않았다면
						//if (!check[next_pos])
						if (check[next_pos] == 0)
						{
							//다음 행선지를 기록하고 check 배열에 움직임의 횟수를 저장
							//bfs_q.push(make_pair(next_pos, move + 1));
							bfs_q.push(next_pos);
							check[next_pos] = check[cur_pos] + 1;
						}
					}
					break;
				}
			}

		}

	}
}

int main(void)
{
	//수빈이와 동생의 위치를 입력받는다
	cin >> N >> K;

	//check 배열에 대해 0으로 초기화
	memset(check, 0, sizeof(check));
	
	// 동생을 찾은 위치를 저장하기 위한 res 변수 선언 및 초기화
	int res = bfs(N, K);

	//큐에 남아있는 노드를 모두 반환하기 위한 루프
	while (!bfs_q.empty()) { bfs_q.pop(); };

	//결과 출력
	cout << res << endl;

	return 0;
}
