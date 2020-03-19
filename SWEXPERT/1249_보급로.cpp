#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 5;
const int INF = 987654321;

struct XY
{
	int y, x;
	int time;
};

int t;
int n;
int MAP[MAX][MAX];
int visited[MAX][MAX];

XY start;
XY desination;

int X[4] = { 1, -1, 0, 0 };
int Y[4] = { 0, 0, 1, -1 };

int result;

// 최소 시간이 걸리는 경로를 찾기위해 INF로 초기화
void init()
{
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			visited[y][x] = INF;
		}
	}
}

// BFS
void solve()
{

	init();
	desination.y = desination.x = n - 1;
	result = INF;

	queue<XY> q;
	q.push(start);
	visited[start.y][start.x] = -1;

	while (!q.empty())
	{
		
		XY now = q.front(); q.pop();
		
		// 도착지에 도착하면 이동시간을 체크
		if (now.x == n - 1 && now.y == n - 1)
		{
			result = min(result, now.time);
			continue;
		}

		XY next;

		// 우회해서 갈 수 있으므로 동서남북 4방향을 다 확인
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];
			next.time = now.time + MAP[next.y][next.x];

			// 범위 체크
			if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
				continue;

			// next.y, next.x의 도착하는 여러가지 방법 중
			// 최소시간이 걸리는 경우만 큐에 푸시
			// visited에 최소 시간을 업데이트
			if (next.time < visited[next.y][next.x])
			{
				visited[next.y][next.x] = next.time;
				q.push(next);
			}
		}
	}
}

// 입력
void input()
{
	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			char c; cin >> c;

			int d = c - '0';
			MAP[y][x] = d;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		input();
		solve();
		
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}