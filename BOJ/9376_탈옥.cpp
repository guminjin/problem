#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 2;
const int INF = 987654321;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;
	int turn;

	bool operator <(INFO now) const
	{
		return turn > now.turn;
	}
};

int garo, sero;
char map[MAX][MAX];
int arr[3][MAX][MAX];
bool visited[MAX][MAX];
XY cleaner[2];
XY dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int result = INF;

void bfs(int idx, XY start)
{
	priority_queue<INFO> q;
	q.push({ start.y, start.x, 0 });
	arr[idx][start.y][start.x] = 0;
	visited[start.y][start.x] = true;

	while (!q.empty())
	{
		INFO now = q.top(); q.pop();
		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + dir[i].y;
			next.x = now.x + dir[i].x;
			next.turn = now.turn;

			if (next.y <0 || next.x<0 || next.y >sero + 1 || next.x >garo + 1)
				continue;
			if (arr[idx][next.y][next.x] >= 0)
				continue;
			if (map[next.y][next.x] == '*')
				continue;
			if (map[next.y][next.x] == '#')
				next.turn++;

			visited[next.y][next.x] = true;
			arr[idx][next.y][next.x] = next.turn;
			q.push(next);
		}
	}
}
void input()
{
	int idx = 0;
	cin >> sero >> garo;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c;

			if (c == '$')
				cleaner[idx++] = { y, x };
		}
	}

	result = INF;
	for (int i = 0; i < 3; i++)
	{
		for (int y = 0; y <= sero + 1; y++)
		{
			for (int x = 0; x <= garo + 1; x++)
			{
				arr[i][y][x] = -1;
			}
		}
	}
}
 
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int tc; cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		input();

		bfs(0, { 0, 0 });
		bfs(1, { cleaner[0].y, cleaner[0].x });
		bfs(2, { cleaner[1].y, cleaner[1].x });

		for (int y = 0; y <= sero + 1; y++)
		{
			for (int x = 0; x <= garo + 1; x++)
			{
				int sum = arr[0][y][x] + arr[1][y][x] + arr[2][y][x];

				if (map[y][x] == '#')
					sum -= 2;

				if (sum >= 0)
					result = min(result, sum);
			}
		}

		cout << result << '\n';
	}
	return 0;
}
