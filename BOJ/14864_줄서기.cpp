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

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int n, m; cin >> n >> m;
	
	vector<int> v(n + 1);
	for (int i = 1; i <= n; i++)
		v[i] = i;

	for (int i = 0; i < m; i++)
	{
		int a, b; cin >> a >> b;
		v[a]++;
		v[b]--;
	}

	bool flg = true;
	vector<bool> visit(n + 1);
	for (int i = 1; i <= n; i++)
	{
		if (visit[v[i]])
		{
			flg = false;
			break;
		}
		visit[v[i]] = true;
	}

	if (flg)
	{
		for (int i = 1; i <= n; i++)
			cout << v[i] << ' ';
		cout << '\n';
	}
	else
		cout << "-1\n";

	return 0;
}
