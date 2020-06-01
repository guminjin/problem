#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

struct INFO
{
	int y, x;
};

const int MAX = 1000;
const int INF = 987654321;

int n;
int arr[MAX][MAX];
int visit[MAX][MAX];

int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };
int mx;
int num;

// 거리측정
int dfs(INFO now)
{
	// 해당 위치에서 갈 수 있는 거리
	int &ret = visit[now.y][now.x];

	// -1이 아니라면 이미 거리 측정된 곳
	if (ret != -1)
		return ret;

	ret = 1;
	INFO next;
	// 상,하,좌,우 네방향을 모두 확인
	for (int i = 0; i < 4; i++)
	{
		next.y = now.y + Y[i];
		next.x = now.x + X[i];

		// 범위 확인
		if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
			continue;
		// 이전의 위치보다 1큰지 확인
		if (arr[next.y][next.x] != arr[now.y][now.x] + 1)
			continue;

		ret += dfs(next);
	}

	return ret;
}


void solve()
{
	// 모든 위치에서 갈 수 있는 거리 
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			// 거리 측정
			int dist = dfs({ y, x });

			// 거리가 mx보다 크다면 값 갱신
			if (dist > mx)
			{
				mx = dist;
				num = arr[y][x];
			}
			// 거리가 mx와 같고, 해당 위치의 방번호가 num보다 작다면
			else if (dist == mx && num > arr[y][x])
			{
				num = arr[y][x];
			}
		}
	}
}

// 입력
void input()
{
	// 초기화
	memset(visit, -1, sizeof(visit));
	mx = -1;
	num = INF;

	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
			cin >> arr[y][x];
	}

}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		input();
		solve();

		cout << '#' << tc << ' ' << num << ' ' << mx << '\n';
	}
	return 0;
}
