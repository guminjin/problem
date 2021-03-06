#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100000 + 5;

struct INFO
{
	int x;
	int lo;
	int time;
};

int n, k;
int map[2][MAX];
bool visit[2][MAX];

bool bfs()
{
	queue<INFO> q;
	q.push({ 0, 0, -1});
	visit[0][0] = true;

	while (!q.empty()) 
	{
		INFO now = q.front(); q.pop();
		if (now.x >= n)
			return true;
		
		int nLo;
		if (now.lo == 0) nLo = 1;
		else nLo = 0;

		// 세가지 행동
		// 1 : 현재 줄의 x위치에서 +1
		// 2 : 현재 줄의 x위치에서 -1
		// 3 : 다른 줄의 x위치에서 +k
		INFO next[3] = { { now.x + 1, now.lo, now.time + 1 },
						 { now.x - 1, now.lo, now.time + 1 },
						 { now.x + k, nLo, now.time + 1 }
						};

		for (int i = 0; i < 3; i++) 
		{
			// 매초 한칸씩 지워지므로, x의 범위 확인
			if (next[i].time >= next[i].x)
				continue;

			// 방문한 위치인지 확인
			if (visit[next[i].lo][next[i].x])
				continue;

			// 해당 위치가 0인지 확인
			if (!map[next[i].lo][next[i].x])
				continue;

			visit[next[i].lo][next[i].x] = true;
			q.push(next[i]);
		}
	}

	return false;
}

// 입력
void input()
{
	// map을 1로 초기화
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < MAX; x++)
		{
			map[i][x] = 1;
		}
	}
	cin >> n >> k;
	
	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < n; x++)
		{
			char c; cin >> c;
			map[i][x] = (c - '0');
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	cout << bfs() << '\n';

	return 0;
}
