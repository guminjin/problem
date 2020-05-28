#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 300 + 3;

struct XY
{
	int y, x;
};

int n;
char m[MAX][MAX];
int bump[MAX][MAX];
bool visit[MAX][MAX];
vector<XY> zero;
int result;

int X[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
int Y[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };

bool visitCheck(int zeroSize)
{
	for (int i = 0; i < zeroSize; i++)
	{
		if (!visit[zero[i].y][zero[i].y])
			return false;
	}
	return true;
}
void copyArr(bool origin[][MAX], bool copy[][MAX])
{
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			copy[y][x] = origin[y][x];
}
void bfs(XY start)
{
	queue<XY> q;
	q.push(start);
	visit[start.y][start.x] = true;

	while (!q.empty())
	{
		XY now = q.front(); q.pop();

		XY next;
		for (int i = 0; i < 8; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];

			if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
				continue;
			if (visit[next.y][next.x])
				continue;

			visit[next.y][next.x] = true;
			if (!bump[next.y][next.x])
				q.push({ next.y, next.x });
		}
	}

}
void dfs(int cnt, int zeroSize)
{
	for (int i = 0; i < zeroSize; i++)
	{
		if (visit[zero[i].y][zero[i].x])
			continue;

		bfs(zero[i]);
		result++;
	}

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (m[y][x] == '*')
				continue;
			if (!visit[y][x])
				result++;
		}
	}
}
void bumpCount()
{
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (m[y][x] == '*')
			{
				bump[y][x] = -1;
				continue;
			}

			int cnt = 0;
			for (int i = 0; i < 8; i++)
			{
				int nx, ny;
				ny = Y[i] + y;
				nx = X[i] + x;

				if (ny < 0 || nx < 0 || ny >= n || nx >= n)
					continue;
				if (m[ny][nx] == '*')
					cnt++;
			}

			if (cnt == 0)
				zero.push_back({ y, x });
			bump[y][x] = cnt;
		}
	}
}
void input()
{
	result = 0;
	zero.clear();
	memset(visit, false, sizeof(visit));

	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> m[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		input();
		bumpCount();
		int zeroSize = zero.size();
		dfs(0, zeroSize);

		cout << '#' << t << ' ' << result << '\n';
	}
	return 0;
}
