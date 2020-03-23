#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 40 + 1;
const int MAX_STIKER = 10;
const int MAX_STIKER_CNT = 100 + 1;

struct XY
{
	int y, x;
};

int garo, sero, k;

int laptop[MAX][MAX];
bool visited[MAX][MAX];

int stiker[MAX_STIKER_CNT][MAX_STIKER][MAX_STIKER];
XY stikerXY[MAX_STIKER_CNT];

int result;


void print()
{
	cout << endl;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
			cout << visited[y][x] << ' ';

		cout << endl;
	}
}

void count()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
			if (visited[y][x])
				result++;
	}
}
void copyStiker(int origin[][MAX_STIKER], int copy[][MAX_STIKER])
{
	for (int y = 0; y < MAX_STIKER; y++)
	{
		for (int x = 0; x < MAX_STIKER; x++)
		{
			copy[y][x] = origin[y][x];
		}
	}
}

void turnStiker(int idx)
{
	int arr[MAX_STIKER][MAX_STIKER];

	for (int oy = 0, cx = 0; oy < MAX_STIKER, cx<MAX_STIKER; oy++, cx++)
	{
		for (int ox = 0, cy = MAX_STIKER-1; ox< MAX_STIKER, cy>=0; ox++, cy--)
		{
			arr[oy][ox] = stiker[idx][cy][cx];
		}
	}
	copyStiker(arr, stiker[idx]);
}

void attachStiker(XY start, XY range[2], int idx)
{
	for (int y = start.y, sy = range[0].y; sy <= range[1].y; y++, sy++)
	{
		for (int x = start.x, sx = range[0].x; sx <= range[1].x; x++, sx++)
		{
			if (stiker[idx][sy][sx])
				visited[y][x] = true;
		}
	}
}
bool checkAttach(XY start, XY range[2], int idx)
{
	for (int y = start.y, sy = range[0].y; sy <= range[1].y; y++, sy++)
	{
		for (int x = start.x, sx = range[0].x; sx <= range[1].x; x++, sx++)
		{
			if (visited[y][x] && stiker[idx][sy][sx])
				return false;
		}
	}

	return true;
}

bool checkRange(int start, int r1, int r2, int len)
{
	int check = start + (r2 - r1);
	
	if (check >= len)
		return false;

	return true;
}

void solve()
{
	for (int i = 0; i < k; i++)
	{
		XY now = stikerXY[i];
		XY range[4][2] = {	
							{ {0, 0},									{now.y - 1, now.x - 1}},
							{ {0, MAX_STIKER -now.y},					{now.x - 1, MAX_STIKER -1}},
							{ {MAX_STIKER - now.y, MAX_STIKER - now.x},	{ MAX_STIKER - 1, MAX_STIKER - 1}},
							{ {MAX_STIKER - now.x, 0},					{ MAX_STIKER - 1, now.y - 1}}
						};

		bool flg = false;
		int idx = 0;
		while (1)
		{
			for (int y = 0; y < sero; y++)
			{
				if (flg)
					break;
				if (!checkRange(y, range[idx][0].y, range[idx][1].y, sero))
					break;
				for (int x = 0; x < garo; x++)
				{
					if (!checkRange(x, range[idx][0].x, range[idx][1].x, garo))
						break;

					if (checkAttach({ y,x }, range[idx], i))
					{
						attachStiker({ y,x }, range[idx], i);
						flg = true;
						break;
					}
				}
			}

			if (flg)
				break;

			if (idx++ == 3)
				break;

			turnStiker(i);
		}
		//print();
	}
}
void input()
{
	cin >> sero >> garo >> k;
	for (int i = 0; i < k; i++)
	{
		int sy, sx; cin >> sy >> sx;
		stikerXY[i] = { sy, sx };

		for (int y = 0; y < sy; y++)
		{
			for (int x = 0; x < sx; x++)
			{
				cin >> stiker[i][y][x];
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();
	count();
	
	cout << result << '\n';
	return 0;
}
