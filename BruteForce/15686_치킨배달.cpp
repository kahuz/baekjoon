//
// 15686 치킨배달
//
// 조건
// - 크기가 NxN 도시가 주어지며, 도시의 각 칸은 빈칸(0), 집(1), 치킨집(2) 중 하나이다
// - 도시의 칸은(x,y)로 나타내고, x,y는 1부터 시작한다
// - 치킨 거리는 집과 가장 가까운 치킨집 사이의 거리를 의미하며, 각각의 집은 치킨거리를 가지고 있다.
// - 도시의 치킨거리는 모든 집의 치킨거리의 합이다
// - 주어진 도시정보에서 치킨집을 M개만 남길 때, 도시의 치킨거리가 가장 작은 값을 구하시오.
//
// 입력
// - 첫째줄 : 지도의 크기 N과 남겨야할 치킨집 M개가 주어진다. ( 2<= N <= 50 ) , ( 1<= M <= 13)
// - 2~N+1줄 : 도시정보
//
// 잘못된 접근
// - 주어진 도시정보에서 치킨집의 위치를 모두 저장하고 ( A개 )
// - 저장된 치킨집에 대해 A Combination M에 대해 구한 다음
// - 모든 경우에 대해 BFS로 최단거리를 구해 값을 저장, res를 갱신해준다
//	-> 시간초과, 조합의 경우 최악 13 Combi 6 ( 1716 ) * 집 100 * 4방향 * 집과치킨거리 ... 이러한 이유로 초과가 뜬 것으로 보임
// 새로운 접근
// - 문제를 잘 읽어보면 치킨과 집과의 거리를 구하는 방법이 나와있다.
// - 그렇다... 주어진 지도는 시작점과 끝점까지 막히는 구간이 없기에 당연히 BFS를 쓰지않고 단순히 xy 좌표로 거리를 구하면 되는 것이다...

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
int map[50][50] = { 0 };

vector<pair<int, int>> init_chicken_v;
vector<pair<int, int>> init_house_v;
bool check[13] = { 0 };
vector<pair<int, int>> chicken_v;

int c_house_num = 0;
int N = 0, M = 0, res = 987534523;

void set_chicken(int idx, int cnt)
{
	if (cnt == M)
	{
		int dist_sum = 0;

		for (int i = 0; i < init_house_v.size(); i++)
		{
			int h_x = init_house_v[i].first;
			int h_y = init_house_v[i].second;
			int dist = 987534523;

			for (int i = 0; i < chicken_v.size(); i++)
			{
				int c_x = chicken_v[i].first;
				int c_y = chicken_v[i].second;
				int tmp_dist = abs(h_x - c_x) + abs(h_y - c_y);

				if (dist > tmp_dist)
					dist = tmp_dist;
			}
			dist_sum += dist;
		}

		if (res > dist_sum)
			res = dist_sum;
		return;
	}

	for (int i = idx; i < c_house_num; i++)
	{
		if (check[i] == false)
		{
			check[i] = true;
			chicken_v.push_back(init_chicken_v[i]);
			set_chicken(i +1, cnt + 1);
			chicken_v.pop_back();
			check[i] = false;
		}
	}
}
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> M;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];

			if (map[y][x] == 2)
			{
				init_chicken_v.push_back(make_pair(x, y));
			}
			else if (map[y][x] == 1)
			{
				init_house_v.push_back(make_pair(x, y));
			}
		}
	}

	c_house_num = init_chicken_v.size();

	set_chicken(0,0);

	cout << res << endl;
	return 0;
}