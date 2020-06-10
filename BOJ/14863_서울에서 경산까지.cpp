#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 5;

struct CITY
{
	int time;
	int money;
};

int n, k;
CITY walk[MAX];
CITY bicycle[MAX];

int result;

void dfs(int now, int time, int total)
{
	if (time > k)
		return;
	if (now == n)
	{
		result = max(result, total);
		return;
	}

	dfs(now + 1, time + walk[now].time, total + walk[now].money);
	dfs(now + 1, time + bicycle[now].time, total + bicycle[now].money);
}
void input()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> walk[i].time >> walk[i].money;
		cin >> bicycle[i].time >> bicycle[i].money;
	}
}
void solve()
{
	result = -1;
	input();
	dfs(0, 0, 0);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	solve();
	cout << result << '\n';
	return 0;
}
