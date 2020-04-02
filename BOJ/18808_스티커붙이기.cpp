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

// 출력
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

// 스티커가 붙여진 위치의 개수 구하기
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

// 스티커를 90도 돌린다.
void turnStiker(int idx)
{
	int arr[MAX_STIKER][MAX_STIKER];

	for (int oy = 0, cx = 0; oy < MAX_STIKER, cx<MAX_STIKER; oy++, cx++)
	{
		for (int ox = 0, cy = MAX_STIKER - 1; ox< MAX_STIKER, cy >= 0; ox++, cy--)
		{
			arr[oy][ox] = stiker[idx][cy][cx];
		}
	}
	copyStiker(arr, stiker[idx]);
}

// 스티커붙이기
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

// 스티커를 붙일 수 있는지 확인
bool checkAttach(XY start, XY range[2], int idx)
{
	for (int y = start.y, sy = range[0].y; sy <= range[1].y; y++, sy++)
	{
		for (int x = start.x, sx = range[0].x; sx <= range[1].x; x++, sx++)
		{
			// 이미 다른 스티커가 붙어 있다면 해당 스티커를 붙일 수 없다.
			if (visited[y][x] && stiker[idx][sy][sx])
				return false;
		}
	}
	return true;
}

// 스티커를 붙일수 있는지 범위를 확인
bool checkRange(int start, int r1, int r2, int len)
{
	int check = start + (r2 - r1);

	// 스티커의 길이가 노트북의 범위를 벗어나면 붙일 수 없다.
	if (check >= len)
		return false;

	return true;
}

void solve()
{
	for (int i = 0; i < k; i++)
	{
		// i번째 스티커의 가로, 세로 크기
		XY now = stikerXY[i];

		// i번째 스티커가 
		// idx 0 : 스티커가 회전하지 않았을 때 스티커가 위치한 범위
		// idx 1 : 스티커가 90도 회전했을 때 스티커가 위치한 범위
		// idx 2 : 스티커가 180도 회전했을 때 스티커가 위치한 범위
		// idx 3 : 스티커가 270도 회전했을 때 스티커가 위치한 범위
		XY range[4][2] = {
			{ { 0, 0 },{ now.y - 1, now.x - 1 } },
		{ { 0, MAX_STIKER - now.y },{ now.x - 1, MAX_STIKER - 1 } },
		{ { MAX_STIKER - now.y, MAX_STIKER - now.x },{ MAX_STIKER - 1, MAX_STIKER - 1 } },
		{ { MAX_STIKER - now.x, 0 },{ MAX_STIKER - 1, now.y - 1 } }
		};

		bool flg = false;
		int idx = 0;

		// 스티커를 회전시킨 모든 경우를 확인
		while (1)
		{
			for (int y = 0; y < sero; y++)
			{
				// flg==true면 이미 스티커가 붙여졌음.
				if (flg)
					break;

				// 스티커를 붙일 수 있는지 세로의 범위 확인
				if (!checkRange(y, range[idx][0].y, range[idx][1].y, sero))
					break;

				for (int x = 0; x < garo; x++)
				{
					// 스티커를 붙일 수 있는지 가로의 범위 확인
					if (!checkRange(x, range[idx][0].x, range[idx][1].x, garo))
						break;

					// 범위가 확인되었다면 스티커가 붙을 자리에 다른 스티커가 있는지 확인
					if (checkAttach({ y,x }, range[idx], i))
					{
						// 스티커 붙이기
						attachStiker({ y,x }, range[idx], i);
						flg = true;
						break;
					}
				}
			}

			if (flg)
				break;

			// 스티커의 모든 방향이 노트북에 붙일 수 없다.
			if (idx++ == 3)
				break;

			// 스티커 회전
			turnStiker(i);
		}
		//print();
	}
}

// 입력
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
