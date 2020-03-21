#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000;
const double INF = 1e20;

int n, l;
int cost[MAX];
double result;

void solve()
{
	for (int j = l; j <= n; j++)
	{
		for (int i = 0; i <= n - j; i++)
		{
			double sum = 0;

			for (int k = 0; k < j; k++)
			{
				sum += cost[i + k];
			}

			result = min(result, sum / j);
		}
	}
}
void input()
{
	cin >> n >> l;

	for (int i = 0; i < n; i++)
		cin >> cost[i];
}

void init()
{
	result = INF;
	memset(cost, 0, sizeof(cost));
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		init();
		input();
		solve();

		cout << result << '\n';
	}
	return 0;
}
