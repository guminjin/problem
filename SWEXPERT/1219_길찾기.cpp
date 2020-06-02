#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100;

int n;
vector<int> v[MAX];
bool visit[MAX];
bool result;

void go(int now)
{
	if (now == 99)
	{
		result = true;
		return;
	}
	for (int i = 0; i < v[now].size(); i++)
	{
		if (visit[now])
			continue;

		visit[now] = true;
		go(v[now][i]);
		visit[now] = false;

		if (result)
			return;
	}
}

// ют╥б
void input()
{
	result = false;
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < MAX; i++)
		v[i].clear();
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	for (int tc = 1; tc <= 10; tc++)
	{
		int t; cin >> t;
		input();
		go(0);
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}
