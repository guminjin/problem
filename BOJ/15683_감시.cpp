#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 8 + 1;
const int INF = 987654321;

struct INFO
{
	int num;	// Number
	int y, x;	// Location
	int dir[4];	// Initial Location
	int dirLen; // Initial Location Length
	int turn;	// Initial Location's turn count
};

int sero, garo;		// column, row
int MAP[MAX][MAX];	
INFO CCTV[8];
int cctvCnt;
int X[4] = { 1, 0, -1, 0 };
int Y[4] = { 0, 1, 0, -1 };
int mn = INF;

// map copy
void copyMAP(int origin[][MAX], int copy[][MAX])
{
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			copy[y][x] = origin[y][x];
		}
	}
}
// count Blind Spot count
void countBlindSpot()
{
	int cnt = 0;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			// map[y][x] == 0
			if (!MAP[y][x])
				cnt++;
		}
	}
	// compare min value
	if (cnt < mn)
		mn = cnt;
}
// cctv can watch area
void watch(int num, int x, int y, int dir)
{
	int nx = x;
	int ny = y;
	while (1)
	{
		nx += X[dir]; ny += Y[dir];
		// range check
		if (nx < 1 || ny < 1 || nx > garo || ny > sero)
			break;
		// if next area is wall, stop
		if (MAP[ny][nx] == 6)
			break;
		if (MAP[ny][nx])
			continue;

		MAP[ny][nx] = num;
	}
}
// check all condition
void bruteforce(int num)
{
	if (num >= cctvCnt)
	{
		countBlindSpot();
		return;
	}

	INFO now = CCTV[num];
	int copy[MAX][MAX];
	copyMAP(MAP, copy);
	for (int i = 0; i < now.turn; i++)
	{
		for (int j = 0; j < now.dirLen; j++)
		{
			watch(now.num, now.x, now.y, now.dir[j]);
			// turn 90
			now.dir[j] = (now.dir[j] + 1) % 4;
		}
		// next cctv
		bruteforce(num + 1);
		copyMAP(copy, MAP);
	}
}
void solve()
{
	bruteforce(0);
}
void input()
{
	cin >> sero >> garo;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			cin >> MAP[y][x];

			if (MAP[y][x] > 0 && MAP[y][x] < 6)
			{
				CCTV[cctvCnt].y = y;
				CCTV[cctvCnt].x = x;

				// init
				switch (MAP[y][x])
				{
				case 1:
					CCTV[cctvCnt].num = 1;
					CCTV[cctvCnt].dir[0] = 0;
					
					CCTV[cctvCnt].dirLen = 1;
					
					CCTV[cctvCnt].turn = 4;
					break;
				case 2:
					CCTV[cctvCnt].num = 2;

					CCTV[cctvCnt].dir[0] = 0;
					CCTV[cctvCnt].dir[1] = 2;
					
					CCTV[cctvCnt].dirLen = 2;
					
					CCTV[cctvCnt].turn = 2;
					break;
				case 3:
					CCTV[cctvCnt].num = 3;

					CCTV[cctvCnt].dir[0] = 0;
					CCTV[cctvCnt].dir[1] = 3;
					
					CCTV[cctvCnt].dirLen = 2;
					
					CCTV[cctvCnt].turn = 4;
					break;
				case 4:
					CCTV[cctvCnt].num = 4;

					CCTV[cctvCnt].dir[0] = 0;
					CCTV[cctvCnt].dir[1] = 3;
					CCTV[cctvCnt].dir[2] = 2;
					
					CCTV[cctvCnt].dirLen = 3;
					
					CCTV[cctvCnt].turn = 4;
					break;
				case 5:
					CCTV[cctvCnt].num = 5;

					CCTV[cctvCnt].dir[0] = 0;
					CCTV[cctvCnt].dir[1] = 1;
					CCTV[cctvCnt].dir[2] = 2;
					CCTV[cctvCnt].dir[3] = 3;
					
					CCTV[cctvCnt].dirLen = 4;
					
					CCTV[cctvCnt].turn = 1;
					break;
				}
				cctvCnt++;
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	input();
	solve();

	cout << mn << '\n';
	return 0;
}
