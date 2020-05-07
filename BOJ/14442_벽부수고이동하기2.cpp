#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000 + 1;

struct INFO
{
	int x, y;
	int dis;
	int wall;

	bool operator< (INFO now) const
	{
		return dis > now.dis;
	}
};

int garo, sero, k;
int map[MAX][MAX];
bool visit[11][MAX][MAX];
// 상->하->좌->우
int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };

// bfs
int solve()
{
	// dis 기준으로 오름차순 정렬
	priority_queue<INFO> q;
	q.push({ 0, 0, 1, 0 });

	for (int i = 0; i < 11; i++)
		visit[i][0][0] = true;;

	// 큐가 빌때까지 수행 => 나가는 경로 없음
	while (!q.empty())
	{
		INFO now = q.top(); q.pop();

		// 목적지에 도착했는지 확인
		if (now.y == sero - 1 && now.x == garo - 1)
			return now.dis;

		INFO next;
		// 상->하->좌->우 네방향 확인
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];
			next.dis = now.dis + 1;
			next.wall = now.wall;

			// 범위 확인
			if (next.y < 0 | next.x < 0 || next.y >= sero || next.x >= garo)
				continue;
			// 방문 확인
			if (visit[next.wall][next.y][next.x])
				continue;
			// 해당 위지가 벽이라면 벽을 부술 수 있는지 확인
			if (map[next.y][next.x])
			{
				// 이미 k개 부섰다면 continue
				if (next.wall == k)
					continue;
				// 벽을 하나 부순다.
				else
					next.wall++;
			}
			
			visit[next.wall][next.y][next.x] = true;
			q.push(next);
		}
	}
	return -1;
}

// 입력
void input()
{
	cin >> sero >> garo >> k;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c - '0';
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	priority_queue<INFO> test;
	
	input();
	cout << solve() << '\n';

	return 0;
}
