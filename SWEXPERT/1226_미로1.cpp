#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 16;

struct XY
{
	int y, x;
};

int m[MAX][MAX];
XY start;
XY destination;
bool visit[MAX][MAX];

XY dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

bool bfs()
{
	// visit배열 초기화
	memset(visit, 0, sizeof(visit));

	queue<XY> q;
	q.push(start);
	visit[start.y][start.x] = true;

	while (!q.empty())
	{
		XY now = q.front(); q.pop();
		// 목적지에 도착했는지 확인
		if (now.y == destination.y && now.x == destination.x)
			return true;

		XY next;
		// 상하좌우 네방향으로 이동
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + dir[i].y;
			next.x = now.x + dir[i].x;

			// 범위 확인
			if (next.y < 0 || next.x < 0 || next.y >= MAX || next.x >= MAX)
				continue;
			// 방문 확인
			if (visit[next.y][next.x])
				continue;
			// 벽 확인
			if (m[next.y][next.x] == 1)
				continue;

			q.push(next);
			visit[next.y][next.x] = true;
		}
	}

	return false;
}

// 입력
void input()
{
	int num; cin >> num;
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			char c; cin >> c;

			m[y][x] = c - '0';
			
			if (m[y][x] == 2)
				start = { y, x };
			if (m[y][x] == 3)
				destination = { y, x };
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);
	
	for (int tc = 1; tc <= 10; tc++)
	{
		input();
		cout << '#' << tc << ' ' << bfs() << '\n';
	}
	return 0;
}
