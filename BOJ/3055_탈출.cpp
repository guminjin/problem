#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 50 + 1;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;
	int type;
	int time;
};

int garo, sero;
char map[MAX][MAX];
int visited[MAX][MAX];
XY dir[4] = { { 0, 1 },{ 0, -1 },{ 1, 0 },{ -1, 0 } };
XY target;
vector<XY> water;

int bfs()
{
	queue<INFO> q;
	for (int i = 0; i < water.size(); i++)
		q.push({ water[i].y, water[i].x, 0, 0 });
	q.push({ target.y, target.x, 1, 0 });
	
	visited[target.y][target.x] = true;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;
		if (now.type)
		{
			if (map[now.y][now.x] == 'D')
				return now.time;
	
			for (int i = 0; i < 4; i++)
			{
				next.x = now.x + dir[i].x;
				next.y = now.y + dir[i].y;
				next.type = 1;
				next.time = now.time + 1;

				if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
					continue;
				if (map[next.y][next.x] == '*' || map[next.y][next.x] == 'X')
					continue;
				if (visited[next.y][next.x])
					continue;
				
				visited[next.y][next.x] = true;
				q.push(next);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				next.x = now.x + dir[i].x;
				next.y = now.y + dir[i].y;
				next.type = 0;
				next.time = now.time + 1;

				if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
					continue;
				if (map[next.y][next.x] == '*' || map[next.y][next.x] == 'X' || map[next.y][next.x] == 'D')
					continue;

				map[next.y][next.x] = '*';
				q.push(next);
			}
		}
	}
	return -1;
}
void input()
{
	cin >> sero >> garo;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c;
			if (c == 'S')
			{
				target.y = y;
				target.x = x;
			}
			else if (c == '*')
			{
				water.push_back({ y, x });
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	int result = bfs();
	if (result != -1)
		cout << result << '\n';
	else
		cout << "KAKTUS\n";

	return 0;
}
