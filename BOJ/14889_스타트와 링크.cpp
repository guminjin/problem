#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20 + 1;
const int INF = 987654321;

int n;
int mn = INF;
int S[MAX][MAX];
bool person[MAX];

// ability calculation
void calAbility()
{
	int start = 0;
	int link = 0;

	for (int y = 1; y <= n; y++)
	{
		for (int x = y; x <= n; x++)
		{
			if (x == y)
				continue;
			
			if (person[x] && person[y])
			{
				start += S[y][x];
				start += S[x][y];
			}
			else if (!person[x] && !person[y])
			{
				link += S[y][x];
				link += S[x][y];
			}
		}
	}

	int dif = abs(start - link);

	if (mn > dif)
		mn = dif;
}
// team select
void dfs(int num, int cnt)
{
	if (cnt == (n / 2))
	{
		calAbility();
		return;
	}
	for (int i = num; i <= n; i++)
	{
		if (person[i])
			continue;

		person[i] = true;
		dfs(i + 1, cnt + 1);
		person[i] = false;
	}
}
void input()
{
	cin >> n;
	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			cin >> S[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	input();
	dfs(1, 0);
	cout << mn << '\n';
	return 0;
}
