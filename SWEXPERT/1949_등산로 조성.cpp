#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 8 + 1;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;
	int cnt;

};

int n, k;
int m[MAX][MAX];
bool visit[MAX][MAX];
vector<XY> start;
int mx;

XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

// 길찾기
void findRoad(XY now, int cmpNum, int cnt, bool flg)
{
	if (cmpNum <= 0)
	{
		mx = max(mx, cnt);
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		XY next;
		next.y = now.y + dir[i].y;
		next.x = now.x + dir[i].x;

		if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
			continue;
		if (visit[next.y][next.x])
			continue;


		if (m[next.y][next.x] - k >= cmpNum)
		{
			mx = max(mx, cnt);
			continue;
		}

		visit[next.y][next.x] = true;

		if (m[next.y][next.x] < cmpNum)
			findRoad(next, m[next.y][next.x], cnt + 1, flg);
		else if (m[next.y][next.x] >= cmpNum && !flg)
			findRoad(next, cmpNum - 1, cnt + 1, 1);

		visit[next.y][next.x] = false;
	}
}

// 입력
void input()
{
	int high = -1;
	cin >> n >> k;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> m[y][x];

			high = max(high, m[y][x]);
		}
	}

	// 시작점 찾기
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (m[y][x] == high)
				start.push_back({ y, x });
		}
	}
}
void solve()
{
	mx = -1;
	start.clear();

	input();

	for (int i = 0; i < start.size(); i++)
	{
		visit[start[i].y][start[i].x] = true;
		findRoad(start[i], m[start[i].y][start[i].x], 1, 0);
		visit[start[i].y][start[i].x] = false;

	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	//freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		solve();
		cout << '#' << tc << ' ' << mx << '\n';
	}
	return 0;
}
