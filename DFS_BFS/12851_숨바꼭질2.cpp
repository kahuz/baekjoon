#include <iostream>		//	io
#include <queue>		//	queue

using namespace std;

//입력된 수빈이의 위치와 동생의 위치를 저장할 변수 선언 및 초기화
int N = 0, K = 0;

//중복 방문을 방지하기 위한 배열 선언 및 초기화
//check range 0 ~ 100000 이므로 배열 크기를 100001으로 선언
bool check[100001] = { 0 };
//탐색 깊이의 제한을 두기 위한 변수 선언 및 초기화
int search_limit = 100001;
//가장 빠르게 찾은 방법의 개수 ( 동생의 위치에 도달한 탐색 깊이에 존재하는 같은 방법의 수 )
int search_cnt = 0;

//bfs 탐색을 위한 변수 선언
queue<pair< int, int>> bfs_q;

//param : 수빈이의 위치와 동생의 위치를 입력으로 받는다
//디버깅을 편하게 하기 위해 매개변수화함
int bfs(int soobin_pos, int brother_pos)
{
	//res는 가장 빨리 동생에게 도달한 방법의 개수를 위한 변수
	int res = 0;

	//초기 수빈이의 위치를 탐색 시작 위치로 큐에 삽입 시작 깊이는 0에서 시작
	bfs_q.push(make_pair(soobin_pos, 0));
	//수빈이의 시작 위치를 방문 배열에 표시
	check[soobin_pos] = true;

	//큐가 모두 사용될때까지 루프
	while (!bfs_q.empty())
	{
		//현재 수빈이의 위치값 선언 및 초기화
		int cur_pos = bfs_q.front().first;
		//수빈이가 동생을 찾기 위해 이동한 횟수( 탐색의 깊이 ) 선언 및 초기화
		int depth = bfs_q.front().second;

		//다음 위치 값을 저장할 변수 선언 및 초기화
		int next_pos = 0;

		//사용한 노드를 큐에서 반환
		bfs_q.pop();

		//현재 위치가 동생의 위치이고 도달한 깊이가 search_limit을 넘지 않은 경우 ( 최초로 동생에게 도달한 걸음 (탐색 깊이) 를 제한값으로 가질 수 있게한다 )
		if (cur_pos == brother_pos && depth <= search_limit)
		{
			//최초로 if문이 실행瑛뻑?depth의 값이 search_limit에 입력되고
			//그 이상의 깊이에서 if문에 진입하지 못하도록 하기 위한 구문
			search_limit = depth;
			//최초 도달한 걸음수(탐색깊이)를 결과값에 넣어준다
			res = depth;
			//if문이 호출 될때마다 같은 걸음수(탐색깊이)에서 동생을 찾은 것이므로
			//동일 걸음 수 내 동생을 찾은 횟수만큼 전역변수 search_cnt를 올려준다.
			search_cnt++;
		}

		//방문한 노드를 표시해준다.
		//같은 깊이의 노드들이 해당 위치에 진입할 수 있도록 위치에 대한 정보를 push할때가 아닌
		//큐의 정보를 가져온 뒤인 시점에 true 표시를 해준다
		check[cur_pos] = true;

		//현재 위치가 변화할 수 있는 3가지 방법에 대해 저의
		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
				//pos - 1
			case 0:
				next_pos = cur_pos - 1;
				break;
				//pos + 1
			case 1:
				next_pos = cur_pos + 1;
				break;
				//pos * 2
			case 2:
				next_pos = cur_pos * 2;
				break;
			}

			//다음 위치가 이동 범위를 넘어서면 무시한다
			if (next_pos < 0 || next_pos > 100000)	continue;
			//다음 위치가 아직 도달하지 않은 곳이라면 다음 위치에 대해 큐에 삽입하여 접근할 수 있도록 한다
			if (check[next_pos] == false)
				bfs_q.push(make_pair(next_pos, depth + 1));
		}
	}

	return res;

}
int main(void)
{
	//문제 풀이시 시간제한을 고려하여 scan_f와 printf와 같은 c lib를 사용하지 않는다면 아래 라인을 꼭 추가해주자
	//cpp iostream 속도 향상을 위해 c lib와의 동기화를 풀어주는 구문
	ios_base::sync_with_stdio(false);

	//수빈이의 위치와 동생의 위치를 입력받는다
	cin >> N >> K;

	//수빈이의 위치와 동생의 위치를 매개변수로 bfs탐색 시작, 동생에게 도달한 걸음수를 반환받아 출력
	//디버깅을 편하게 하기 위해 매개변수화함
	cout << bfs(N, K) << "\n";
	//최종 탐색 방법의 개수를 출력
	cout << search_cnt << endl;


	return 0;
}