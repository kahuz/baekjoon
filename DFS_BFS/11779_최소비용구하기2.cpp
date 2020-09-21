//
// 최대 1,000개의 도시와 100,000개의 버스가 있을때 A번째 도시에서 B번째 도시까지 가는데 드는 버스 비용을 최소화하는 문제 
// 주어지는 두 노드 사이의 최소 비용 경로를 찾는 문제이므로 
// 다익스트라 알고리즘을 적용하여 풀이하면 된다
//
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

//각 구간 비용을 저장할 배열
int dist[1001] = { 0 };
//탐색 경로를 저장할 배열
int path[1001] = { 0 };
//전체 경로와 비용을 저장할 인접리스트 벡터
vector<pair<int, int>> v[1001];
//경로를 출력하기 위한 벡터
vector<int> path_v;
//도시의 개수와 버스의 개수를 입력받을 변수
int N = 0, M = 0;
//출발점과 도착점을 저장할 변수, c++에서 end 는 이미 지정된 변수명이므로 End로 지정
int start = 0, End = 0;
void dijkstra()
{
    //다익스트라를 구현하기위한 우선순위 큐 선언
    priority_queue<pair<int, int>> pq;
    //초기 코스트와 출발점 입력
    pq.push(make_pair(0, start));
    //출발점에 대한 코스트 입력 ( 초기 0 )
    dist[start] = 0;

    //큐가 모두 비워질때까지 탐색
    while (!pq.empty())
    {
        //우선순위 큐는 값이 클 수록 높은 우선순위를 준다
        //따라서 -를 취함으로 최소비용이 가장 높은 값이 될 수 있도록 해주는 것
        //가져올때도 -를 취해 값을 원복하는 것
        int cost = -pq.top().first;
        int cur_node = pq.top().second;

        pq.pop();
        //현재 노드와 연결된 노드들에 대해 탐색
        for (int i = 0; i < v[cur_node].size(); i++)
        {
            //다음 노드 값과 비용을 가져온다
            int next = v[cur_node][i].first;
            int cost_n = v[cur_node][i].second;

            //최소비용 갱신을 위해 이전에 기록한 next 노드의 비용 값과 현재 가져온 비용값 비교
            if (dist[next] > cost + cost_n)
            {
                //경로와 비용을 갱신 및 다음 탐색 구간 입력
                path[next] = cur_node;
                dist[next] = cost + cost_n;
                pq.push(make_pair(-dist[next], next));
            }
        }
    }
    //도착지에 대한 비용 출력
    cout << dist[End] << endl;
    //경로 탐색을 위한 변수 선언
    int path_value = End;
    //도착지를 기준으로 배열 값을 가져온다. 출발지에 도달 시 0값이 되므로 while 종료
    while (path_value)
    {
        //도착지부터 출발점까지 벡터에 삽입
        path_v.push_back(path_value);
        //path_value를 통해 이전 경로를 찾아간다
        path_value = path[path_value];
    }
    //도착지 - 출발지 구간이 몇개인지 벡터 사이즈로 출력
    cout << path_v.size() << endl;
    //벡터 순회로 출발-도착지에 대한 경로 출력
    for (int i = path_v.size() - 1; i >= 0; i--) 
        cout << path_v[i] << " ";

    cout << endl;

}

int main(void)
{
    //도시와 버스에 대한 값을 입력받는다
    cin >> N >> M;
    //구간 비용을 최대값으로 초기화
    for (int i = 1; i <= N; i++) 
        dist[i] = 1e9;
    
    //각 연결 구간에 대한 비용을 입력받는다
    for (int i = 0; i < M; i++)
    {
        int cur_node, next_node, cost; 
        cin >> cur_node >> next_node >> cost;
        
        v[cur_node].push_back(make_pair(next_node, cost));
    }
    //마지막 라인의 출발지와 도착지를 입력받는다
    cin >> start >> End;

    //다익스트라 실행
    dijkstra();

    return 0;
}
