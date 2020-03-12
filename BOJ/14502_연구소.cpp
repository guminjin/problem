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

int n, m;
int map[MAX][MAX];
int copy_map[MAX][MAX];
queue<Info> virus;
Info dir[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int mx = 0;

void print(int arr[][MAX])
{
	cout << endl;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cout << arr[y][x] << ' ';
		}
		cout << endl;
	}
}
void BFS()
{
	queue<Info> q;

	int virus_cnt = virus.size();
	for (int i = 0; i < virus_cnt; i++)
	{
		Info temp = virus.front();
		q.push(temp);
		virus.pop(); virus.push(temp);
	}

	int arr[MAX][MAX];
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			arr[y][x] = copy_map[y][x];
		}
	}

	while (!q.empty())
	{
		Info now = q.front(); q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nx = now.x + dir[i].x;
			int ny = now.y + dir[i].y;

			if (nx < 0 || ny < 0 || nx >= m || ny >= n)
				continue;
			if (arr[ny][nx] != 0)
				continue;

			q.push({ nx, ny });
			arr[ny][nx] = 2;
		}
	}

	int cnt = 0;

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (arr[y][x] == 0)
				cnt++;
		}
	}
	//print(arr);
	//cout << cnt << endl;
	//cout << endl;
	if (mx < cnt)
		mx = cnt;
}

void DFS(int startX, int startY, int cnt)
{
	if (cnt == 3)
	{
		BFS();
		return;
	}

	for (int y = startY; y < n; y++)
	{
		for (int x = startX; x < m; x++)
		{
			if (copy_map[y][x] == 0)
			{
				copy_map[y][x] = 1;

				DFS(x, y, cnt + 1);

				copy_map[y][x] = 0;
			}
		}
		startX = 0;
	}
}

void map_Copy()
{
	memset(copy_map, 0, sizeof(copy_map));

	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
			copy_map[y][x] = map[y][x];
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> m;

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cin >> map[y][x];
			if (map[y][x] == 2)
				virus.push({ x,y });
		}
	}
	map_Copy();
	DFS(0, 0, 0);

	cout << mx << '\n';
	return 0;
}