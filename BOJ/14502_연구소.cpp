#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'
typedef long long ll;

const int MAX = 8;

struct Info
{
	int x, y;
};

int inning, m;
int map[MAX][MAX];
queue<Info> virus;
Info dir[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int mx;

// map print
void print(int arr[][MAX])
{
	cout << endl;
	for (int y = 0; y < inning; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cout << arr[y][x] << ' ';
		}
		cout << endl;
	}
}
// count safeZone
void countSafezone(int arr[][MAX])
{
	int cnt = 0;
	for (int y = 0; y < inning; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (arr[y][x] == 0)
				cnt++;
		}
	}

	if (mx < cnt)
		mx = cnt;
}
// array copy
void copy(int origin[][MAX], int copy[][MAX] )
{
	memset(copy, 0, sizeof(copy));

	for (int y = 0; y < inning; y++)
		for (int x = 0; x < m; x++)
			copy[y][x] = origin[y][x];
}
// spread virus
void BFS()
{
	queue<Info> q;

	// all virus spread at the same time
	int virus_cnt = virus.size();
	for (int i = 0; i < virus_cnt; i++)
	{
		Info temp = virus.front();
		q.push(temp);
		virus.pop(); virus.push(temp);
	}

	int arr[MAX][MAX];
	copy(map, arr);

	while (!q.empty())
	{
		Info now = q.front(); q.pop();
		Info next;
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;

			if (next.x < 0 || next.y < 0 || next.x >= m || next.y >= inning)
				continue;
			if (arr[next.y][next.x] != 0)
				continue;

			q.push(next);
			arr[next.y][next.x] = 2;
		}
	}
	countSafezone(arr);
}
// wall erating
void DFS(int startX, int startY, int cnt)
{
	if (cnt == 3)
	{
		BFS();
		return;
	}

	for (int y = startY; y < inning; y++)
	{
		for (int x = startX; x < m; x++)
		{
			if (map[y][x] == 0)
			{
				map[y][x] = 1;

				DFS(x, y, cnt + 1);

				map[y][x] = 0;
			}
		}
		startX = 0;
	}
}
void solve()
{
	DFS(0, 0, 0);
}
void input()
{
	cin >> inning >> m;

	for (int y = 0; y < inning; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cin >> map[y][x];
			if (map[y][x] == 2)
				virus.push({ x,y });
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();
	
	cout << mx << '\n';
	return 0;
}