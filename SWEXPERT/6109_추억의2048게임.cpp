#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20 + 2;

int n;
string s;
int map[MAX][MAX];

void print()
{
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cout << map[y][x] << ' ';
		}
		cout << '\n';
	}
}
void removeZero()
{
	for (int x = 0; x < n; x++)
	{
		int idx = 0;
		for (int y = 0; y < n; y++)
		{
			if (map[y][x] == 0)
				y++;

			map[idx++][x] = map[y][x];
		}
		for (int y = idx; y < n; y++)
			map[y][x] = 0;
		
	}
}
void up()
{
	removeZero();
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n - 1; y++)
		{
			if (map[y][x] != map[y + 1][x])
				continue;
			
			map[y][x] *= 2;
			map[y + 1][x] = 0;
		}
	}
	removeZero();
}
void rotate()
{
	int copy[MAX][MAX];
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			copy[x][n-1-y] = map[y][x];
		}
	}
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			map[y][x] = copy[y][x];
		}
	}
}
void solve()
{
	if (s == "up")
	{
		up();
	}
	else if (s == "down")
	{
		for (int i = 0; i < 2; i++)
			rotate();
		up();
		for (int i = 0; i < 2; i++)
			rotate();
	}
	else if (s == "left")
	{
		for (int i = 0; i < 1; i++)
			rotate();
		up();
		for (int i = 0; i < 3; i++)
			rotate();
	}
	else if (s == "right")
	{
		for (int i = 0; i < 3; i++)
			rotate();
		up();
		for (int i = 0; i < 1; i++)
			rotate();
	}
}
void input()
{
	memset(map, 0, sizeof(map));
	cin >> n >> s;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> map[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		input();
		solve();
		cout << '#' << t << '\n';
		print();
	}
	return 0;
}
