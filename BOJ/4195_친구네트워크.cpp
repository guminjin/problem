#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 200000 + 10;

struct INFO
{
	int idx;
	int cnt;
};

int t;
int parent[MAX];
map<string, INFO> m;

void unionParent(int n1, int n2)
{
	if (n1 < n2)
		parent[n2] = n1;
	else
		parent[n1] = n2;
}
int findParent(int num)
{
	if (parent[num] == num)
		return num;

	return findParent(parent[num]);
}
void solve()
{
	int f; cin >> f;
	int idx = 0;

	for (int i = 0; i < f; i++)
	{
		string s1, s2; cin >> s1 >> s2;

		if (m[s1].idx == 0)
		{
			m[s1].idx = idx++;
			m[s1].cnt = 1;
		}
		if (m[s2].idx == 0)
		{
			m[s2].idx = idx++;
			m[s2].cnt = 1;
		}

		int p1 = findParent(m[s1].idx);
		int p2 = findParent(m[s2].idx);

		if (p1 != p2)
		{
			unionParent(p1, p2);

			int t = m[p1].cnt;
			m[p1].cnt += m[p2].cnt;
			m[p2].cnt += t;
		}

		cout << max(m[s1].cnt, m[s2].cnt) << '\n';
	}
}
void init()
{
	m.clear();
	for (int i = 0; i < MAX; i++)
	{
		parent[i] = i;
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	 
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		init();
		solve();
	}
	return 0;
}