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

int stiker[MAX_STIKER_CNT][MAX_STIKER][MAX_STIKER];
XY stikerXY[MAX_STIKER_CNT];

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

	for (int oy = 0,int cx = 0; oy < MAX_STIKER, cx<MAX_STIKER; oy++, cx++)
	{
		for (int ox = 0, cy = MAX_STIKER-1; ox< MAX_STIKER, cy>=0; ox++, cy--)
		{
			arr[oy][ox] = stiker[idx][cy][cx];
		}
	}
	copyStiker(arr, stiker[idx]);
}

bool checkAttach(XY range[2], XY start)
{
	XY check;
	check.x = start.x + (range[1].x - range[0].x);
	check.y = start.y + (range[1].y - range[0].y);

	if (check.x > garo || check.y > sero)
		return false;

	return true;
}
bool checkAttach(XY range[2], XY start)
{
	XY check;
	check.x = start.x + (range[1].x - range[0].x);
	check.y = start.y + (range[1].y - range[0].y);

	if (check.x > garo || check.y > sero)
		return false;

	return true;
}
void solve()
{
	for (int i = 0; i < k; i++)
	{
		XY now = stikerXY[i];
		XY range[4][2] = {	
							{ {0, 0},				  {now.y - 1, now.x - 1} },
							{ {0, MAX_STIKER -now.y}, {now.x-1, MAX_STIKER -1}},
							{ {MAX_STIKER -now.y, 0}, { MAX_STIKER -1, now.x -1}},
							{ {0, 0},				  {now.x -1, now.y -1}} 
						};

		for (int i = 0; i < 4; i++)
		{
			for (int y = 0; y < sero; y++)
			{
				for (int x = 0; x < garo; x++)
				{

				}
			}
		}
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

	return 0;
}
