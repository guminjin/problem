#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000 + 1;
int n, m;
vector<int> v[MAX];
int parent[MAX];
bool visited[MAX];

void dfs(int start, int p)
{
	visited[start] = true;
	for (int i = 0; i < v[start].size(); i++)
	{
		int next = v[start][i];
		if (visited[next])
			continue;
		parent[next] = p;
		dfs(next, p);
	}
}
void solve()
{
	int result = 0;
	for (int i = 1; i <= n; i++)
	{
		if (parent[i] != i)
			continue;
		dfs(i, parent[i]);
		result++;
	}
	cout << result << '\n';
}
void input()
{
	for (int i = 1; i < MAX; i++)
		parent[i] = i;
	
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();
	return 0;
}
