#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 10;
const int MAX_K = 1000 + 10;
const int MAX_BUG = 10000 + 10;
struct BUG
{
	int y, x;
	int size;
	int dir;
	bool live;
};

int n, m, k;
BUG bug[MAX_BUG];

int X[5] = { 0, 0, 0, -1, 1 };
int Y[5] = { 0, -1, 1, 0, 0 };

// 방향 전환
void changeDir(int& dir)
{
	switch (dir)
	{
	case 1:
		dir = 2;
		break;
	case 2:
		dir = 1;
		break;
	case 3:
		dir = 4;
		break;
	case 4:
		dir = 3;
		break;
	}
}

void moveBug()
{
	int arr[MAX][MAX][5];
	memset(arr, 0, sizeof(arr));

	for (int i = 0; i < k; i++)
	{
		BUG &now = bug[i];
		if (!now.live)
			continue;

		now.y += Y[now.dir];
		now.x += X[now.dir];
		
		if (now.y == 0 || now.x == 0 || now.y == n - 1 || now.x == n - 1)
		{
			now.size /= 2;
			changeDir(now.dir);

			if (now.size == 0)
			{
				now.live = false;
				continue;
			}
		}
		int idx = arr[now.y][now.x][0] + 1;
		arr[now.y][now.x][idx] = i + 1;
		arr[now.y][now.x][0]++;
	}

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (arr[y][x][0] <= 1)
				continue;
			
			int mx = 0;
			int idx;
			int sum = 0;
			for (int i = 1; i < 5; i++)
			{
				if (arr[y][x][i] == 0)
					break;

				sum += bug[arr[y][x][i]-1].size;
				if (mx < bug[arr[y][x][i]-1].size)
				{
					mx = bug[arr[y][x][i]-1].size;
					idx = i;
				}
			}
			for (int i = 1; i < 5; i++)
			{
				if (arr[y][x][i] == 0)
					break;

				if (i == idx)
					bug[arr[y][x][i]-1].size = sum;
				else
					bug[arr[y][x][i]-1].live = false;
			}

		}
	}
}

void input()
{

	cin >> n >> m >> k;
	for (int i = 0; i < k; i++)
	{
		int y, x, s, d;
		cin >> y >> x >> s >> d;
		bug[i] = { y, x, s, d, 1};
	}
}

int solve()
{
	input();
	for (int i = 0; i < m; i++)
		moveBug();
	
	int result = 0;
	for (int i = 0; i < k; i++)
	{
		if (bug[i].live)
		{	
			result += bug[i].size;
		}
	}
	return result;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		int result = solve();
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}
