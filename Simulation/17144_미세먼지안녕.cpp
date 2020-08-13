//
// 17144 미세먼지안녕
// 
// 조건
// - 공기청정기 성능 테스트를 위해 집을 크기가 R x C인 격자판으로 나타냈다
// - 각 칸(r,c)에 있는 미세먼지의 양을 실시간으로 모니터링을 개발하였다.
// - 공기청정기는 항상 1번 열에 설치되어 있고, 크기는 두 행을 차지한다.
// - 공기청정기가 설치되어있지 않은 칸에는 미세먼지가 있고 (r,c)에 있는 미세먼지의 양은 A[r][c]이다
// - 1초동안 아래 적힌 일이 순서대로 일어난다.
//	1. 미세먼지가 확산된다. 확산은 미세먼지가 있는 모든 칸에서 동시에 일어난다.
//		->(r,c)에 있는 미세먼지는 인접한 네 방향으로 확산된다
//		->인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
//		->확산되는 양은 A[r][c] / 5 이고, 소수점은 버린다.
//		->(r,c)에 남은 미세먼지의 양은 A[r][c] - (A[r][c] / 5) * (확산된 방향의 개수)이다
//	2. 공기청정기가 작동한다.
//		->공기청정기에서는 바람이 나온다
//		-> 위쪽 공기청정기의 바람은 반시계방향으로 순환하고, 아래쪽 공기청정기의 바람은 시계방향으로 순환한다.
//		-> 바람이 불면 미세먼지가 바람의 방향대로 모두 한칸씩 이동한다.
//		-> 공기청정기에서 부는 바람은 미세먼지가 없는 바람이고, 공기청정기로 들어간 미세먼지는 모두 정화된다.
// - 방의 정보가 주어졌을때, T초가 지난 후 구사과의 방에 남아있는 미세먼지의 양을 구해보자
// 입력
// - 첫째줄에 R(6<=R<=50),C(6<=C<=50),T(1<=T<=1000)이 주어진다
// - 둘째줄부터 R개의 줄에 A[r][c] ( -1 <= A[r][c] <= 1000)이 주어진다.
// - 공기청정기가 설치된 곳은 A[r][c]가 -1이고, 나머지 값은 미세먼지의 양이다. -1은 2번 위아래로 붙어져있고, 가장 윗행, 아랫행과 두칸이상 떨어져있다.
//
// 접근
// - 풀이에 주어진대로 1. 미세먼지 확산을 시킨 뒤 2. 공기청정기가 작동. 을 T 시간동안 반복시킨다
// - 공기 순환을 깔끔하게 짤 방법이 생각나지 않는다... 으음...
#include <iostream>

using namespace std;
//집에 대한 지도 배열 선언 및 초기화
int map[50][50] = { 0 };

//상 우 하 좌
//먼지 확산을 위한 방위 배열 선언 및 초기화
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
//공기청정기 위치를 저장할 배열 선언 및 초기화, 0은 상단 1은 하단
int air_y[2] = { 51,51 };
//집의 크기 R,C와 확산-순환 횟수인 T 변수 선언 및 초기화
int R = 0, C = 0, T = 0;
//결과변수 선언 및 초기화
int res = 0;

//마지막에 남은 미세먼지 양을 체크해준다
void check_dust()
{
	//map 배열을 전체 조회하여 남은 미세먼지만큼 res에 반영
	for (int y = 0; y < R; y++)
	{
		for (int x = 0; x < C; x++)
		{
			if (map[y][x] > 0)
				res += map[y][x];
		}
	}
}
void spread_dust()
{
	//확산된 미세먼지를 기록할 배열 선언 및 초기화
	//모든 미세먼지는 "동시"에 확산 되므로 map에 있는 값이 갱신되서는 안된다
	//따라서 map에 있는 미세먼지에 의해 확산되는 값을 모두 구하고, 그것을 map에 다시 반영해주어야한다
	int spread_map[50][50] = { 0 };
	
	//map 전체 범위를 조회
	for (int y = 0; y < R; y++)
	{
		for (int x = 0; x < C; x++)
		{
			//현재 위치에 대한 미세먼지양을 가져온다
			int dust = map[y][x];

			//먼지 확산 조건 충족 확인
			if (dust > 0)
			{
				int spread_num = 0;
				int spread_volume = map[y][x] / 5;
				//먼지 확산
				for (int i = 0; i < 4; i++)
				{
					int xn = x + dx[i];
					int yn = y + dy[i];

					if (xn < 0 || xn >= C || yn < 0 || yn >= R || map[yn][xn] == -1)	continue;

					spread_map[yn][xn] += spread_volume;
					spread_num++;
				}
				//확산되고 남은 먼지를 map에 재반영
				map[y][x] = map[y][x] - (spread_volume * spread_num);
			}
		}
	}

	//확산된 미세먼지가 기록된 spread_map의 값을 map에 반영해준다
	for (int y = 0; y < R; y++)
	{
		for (int x = 0; x < C; x++)
		{
			map[y][x] += spread_map[y][x];
		}
	}
}
//순수하게 하드코딩으로 공기순환을 표현
void circulate_air()
{
	//윗방향 순환
	for (int x = 0; x < C; x++)
	{
		if (x == 0)
		{
			for (int y = air_y[0]-1; y >= 0; y--)
			{
				if (y == air_y[0] - 1)
					map[y][x] = 0;
				else
					map[y + 1][x] = map[y][x];
			}

		}
		else 
		{
			map[0][x - 1] = map[0][x];
		}
	}

	for (int y = 0; y < air_y[0]; y++)
	{
		map[y][C - 1] = map[y + 1][C - 1];
	}

	for (int x = C - 1; x > 1; x--)
	{
		map[air_y[0]][x] = map[air_y[0]][x - 1];
	}
	map[air_y[0]][1] = 0;

	//아랫방향 순환
	for (int y = air_y[1]+1; y < R-1; y++)
	{
		map[y][0] = map[y + 1][0];
	}
	
	for (int x = 0; x < C-1; x++)
	{
		map[R - 1][x] = map[R - 1][x + 1];
	}

	for (int y = R - 1; y > air_y[1]; y--)
	{
		map[y][C - 1] = map[y - 1][C - 1];
	}

	for (int x = C - 1; x > 1; x--)
	{
		map[air_y[1]][x] = map[air_y[1]][x - 1];
	}
	map[air_y[1]][1] = 0;

}
void start_test(int time)
{
	for (int i = 0; i < time; i++)
	{
		//1. 먼지확산 함수 호출
		spread_dust();
		//2. 공기 순환 함수 호출
		circulate_air();
	}
	check_dust();
}
int main(void)
{
	//지도 크기 및 테스트 시간을 입력받는다
	cin >> R >> C >> T;
	//지도 정보를 입력받기 위해 R , C만큼 loop
	for (int y = 0; y < R; y++)
	{
		for (int x = 0; x < C; x++)
		{
			//지도 정보 입력
			cin >> map[y][x];
			
			//공기청정기 위치 저장
			if (map[y][x] == -1)
			{
				if (air_y[0] > y)
					air_y[0] = y;
				else
					air_y[1] = y;
			}
		}
	}
	//공기청정기 테스트 시작
	start_test(T);
	//결과 출력
	cout << res << endl;
	return 0;
}