#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20 + 1;	

int n;
int map[MAX][MAX];
int mx;

// 배열을 복사
void copyMap(int origin[][MAX], int copy[][MAX])
{
	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			copy[y][x] = origin[y][x];
		}
	}
}

// 최대값 찾기
void maxValue()
{
	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			if (mx < map[y][x])
				mx = map[y][x];
		}
	}
}

// 사이에 있는 0을 제거해 준다
void removeZero()
{
	int temp[MAX][MAX];
	memset(temp, 0, sizeof(temp));
	for (int x = 1; x <= n; x++)
	{
		int idx = 1;
		for (int y = 1; y <= n; y++)
		{
			if (!map[y][x])
				continue;
			temp[idx++][x] = map[y][x];
		}
	}

	copyMap(temp, map);
}

// 위로 이동하고, 합쳐준다
void moveUp()
{
	removeZero();

	for (int x = 1; x <= n; x++)
	{
		for (int y = 1; y <= n; y++)
		{
			if (y >= n)
				break;
			if (map[y][x] != map[y + 1][x])
				continue;

			map[y][x] += map[y + 1][x];
			map[y + 1][x] = 0;
		}
	}

	removeZero();
}

// 90도 회전해준다.
void rotate()
{
	int temp[MAX][MAX];

	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			temp[y][x] = map[n - x + 1][y];
		}
	}

	copyMap(temp, map);
}

// 모든 경우의 수를 모두 해본다.
void dfs(int cnt)
{
	// 5번 이동했다면 최대값을 확인
	if (cnt == 5)
	{
		maxValue();
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int temp[MAX][MAX];
		copyMap(map, temp);

		moveUp();
		dfs(cnt + 1);

		copyMap(temp, map);
		rotate();
	}
}

// 입력
void input()
{
	cin >> n;
	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			cin >> map[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	dfs(0);
	cout << mx << '\n';
	return 0;
}
