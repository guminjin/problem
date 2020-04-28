#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20;
const int INF = 987654321;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;
	int move;
};

int garo, sero;
char map[MAX][MAX];
bool visited[MAX][MAX];
int dis[11][11];

vector<XY> dust;
XY cleaner;
XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

bool check[11];
int result;

void dfs(int start, int len, int cnt, int p_size)
{
	if (cnt == p_size)
	{
		result = min(result, len);
		return;
	}
	for (int i = 1; i <= p_size; i++)
	{
		if (check[i] || start == i)
			continue;
		if (dis[start][i] == 0)
			continue;

		check[i] = true;
		dfs(i, dis[start][i] + len, cnt + 1, p_size);
		check[i] = false;
	}
}
void bfs(XY start, int idx, int p_size)
{
	memset(visited, 0, sizeof(visited));
	int cnt = 0;

	queue<INFO> q;
	q.push({ start.y, start.x, 0 });
	visited[start.y][start.x] = true;
	

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		int p = map[now.y][now.x] - '0';
		if (p >= 0 && p <= 9)
		{
			dis[idx][p] = now.move;
			if (++cnt == p_size)
				return;
		}

		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + dir[i].y;
			next.x = now.x + dir[i].x;
			next.move = now.move + 1;

			if (next.y<0 || next.x<0 || next.y>=sero || next.x >= garo)
				continue;
			if (visited[next.y][next.x])
				continue;
			if (map[next.y][next.x] == 'x')
				continue;

			visited[next.y][next.x] = true;
			q.push(next);
		}
	}
}

bool input()
{
	result = INF;
	memset(dis, 0, sizeof(dis));
	//memset(select, 0, sizeof(select));
	//memset(map, 0, sizeof(map));
	dust.clear();

	int idx = 1;
	cin >> garo >> sero;

	if (garo == 0 && sero == 0)
		return false;
	
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c;

			if (c == 'o')
			{
				cleaner = { y, x };
				map[y][x] = '.';

			}
			else if (c == '*')
			{
				dust.push_back({ y,x });
				map[y][x] = ('0' + idx++);
			}
		}
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	while (input())
	{
		int p_size = dust.size();
		if (p_size == 0)
		{
			cout << "0\n";
			continue;
		}

		bfs(cleaner, 0, p_size);
		for (int i = 1; i <= p_size; i++)
			bfs(dust[i - 1], i, p_size);

		check[0] = true;
		for (int i = 1; i <= p_size; i++)
		{
			check[i] = true;
			dfs(i, dis[0][i], 1, p_size);
			check[i] = false;
		}

		if (result == INF)
			cout << "-1\n";
		else
			cout << result << '\n';
	}
	return 0;
}
