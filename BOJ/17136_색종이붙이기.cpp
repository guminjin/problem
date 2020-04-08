#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 10;
const int INF = 987654321;

struct XY
{
	int y, x;
};
int map[MAX][MAX];
bool paper[5][5] = {	{ 1, 1, 1, 1, 1 },
						{ 1, 1, 1, 1, 1 },
						{ 1, 1, 1, 1, 1 },
						{ 1, 1, 1, 1, 1 },
						{ 1, 1, 1, 1, 1 } 
					};
int paperCnt[6] = { 0, 5, 5, 5, 5, 5 };
int result = INF;

bool checkMap()
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (map[y][x] == 1)
				return false;
		}
	}
	return true;
}
void copyMap(int origin[][MAX], int copy[][MAX])
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
			copy[y][x] = origin[y][x];
	}
}
void attachPaper(XY now, int size)
{
	for (int y = now.y; y < now.y + size; y++)
	{
		for (int x = now.x; x < now.x + size; x++)
		{
			map[y][x] = 0;
		}
	}
}
XY checkAttach(int size)
{
	for (int y = 0; y < MAX - size + 1; y++)
	{
		for (int x = 0; x < MAX - size + 1; x++)
		{
			if (!map[y][x])
				continue;

			bool flg = true;

			for (int cy = y, ny = 0; ny < size; cy++, ny++)
			{
				for (int cx = x, nx = 0; nx < size; cx++, nx++)
				{
					if (map[cy][cx] && paper[ny][nx])
						continue;

					flg = false;
					break;
				}
				if (!flg)
					break;
			}

			if (flg)
				return { y, x };
		}
	}
	return { -1, -1 };
}
void dfs(int cnt)
{
	if (checkMap())
	{
		result = min(result, cnt);
		return;
	}
	for (int i = 5; i >= 1; i--)
	{
		if (paperCnt[i] == 0)
			continue;

		XY lo = checkAttach(i);
		if (lo.x == -1 && lo.y == -1)
			continue;

		int copy[MAX][MAX];
		copyMap(map, copy);

		paperCnt[i]--;
		attachPaper(lo, i);
		dfs(cnt + 1);

		paperCnt[i]++;
		copyMap(copy, map);
	}
}
	

int input()
{
	int ch = 0;
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			cin >> map[y][x];
			if (map[y][x])
				ch++;
		}
	}
	
	return ch;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	int ch = input();
	if (ch == 0)
		cout << "0\n";
	else if (ch == 100)
		cout << "4\n";
	else
	{
		dfs(0);
		if(result == INF)
			cout << "-1\n";
		else
			cout << result << '\n';
	}
	return 0;
}
