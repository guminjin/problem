#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

struct INFO 
{
	int start, des;
};

int n;
vector<INFO> v;
int mxIdx;

void solve()
{
}
void input()
{
	v.clear();
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int s, e; cin >> s >> e;
		v.push_back({ s, e });
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
		cout << '#' << tc << ' ';
	}
	return 0;
}
