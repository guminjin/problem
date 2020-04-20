#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000 + 1;
const int INF = 987654321;

struct INFO
{
	int y, x;
	int time;
	int cnt;
};

int garo, sero;
bool map[MAX][MAX];
bool visited[2][MAX][MAX];
vector<pair<int, int>> v;
int result = INF;

int Y[4] = { 0, 0, -1, 1 };
int X[4] = { 1, -1, 0, 0 }; 

void bfs()
{
	memset(visited, 0, sizeof(visited));
	queue<INFO> q;
	q.push({ 0, 0, 1, 0 });
	visited[0][0][0] = visited[1][0][0] = true;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		if (now.x == garo - 1 && now.y == sero - 1)
		{
			result = min(result, now.time);
			return;
		}

		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + X[i];
			next.y = now.y + Y[i];
			next.time = now.time + 1;
			next.cnt = now.cnt;

			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			if (visited[next.cnt][next.y][next.x])
				continue;
			if (map[next.y][next.x] && next.cnt)
				continue;
			if (map[next.y][next.x] && !next.cnt)
			{
				next.cnt++;
				q.push(next);
				visited[next.cnt][next.y][next.x] = true;
				continue;
			}
			
			visited[next.cnt][next.y][next.x] = true;
			q.push(next);
		}
	}
}

void input()
{
	cin >> sero >> garo;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c - '0';
			
			if (map[y][x])
				v.push_back(make_pair(y, x));
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	bfs();
	if (result == INF)
		cout << "-1\n";
	else
		cout << result << '\n';
	return 0;
}
