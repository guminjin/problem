#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20000 + 1;

int n, m;
vector<int> v[MAX];
bool visited[MAX];
int color[MAX];
bool result;

void dfs(int start, int c)
{
	visited[start] = true;
	color[start] = c;
	for (int i = 0; i < v[start].size(); i++)
	{
		int next = v[start][i];
		if (visited[next])
		{
			if (color[next] == color[start])
			{
				result = false;
				return;
			}

			continue;
		}
		else
		{
			dfs(next, c *-1);
			if (!result)
				return;
		}
	}
}
void input()
{
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
	
	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		for (int i = 0; i < MAX; i++)
		{
			v[i].clear();
			visited[i] = false;
			color[i] = 0;
		}
		result = true;
		input();

		for (int i = 1; i <= n; i++)
		{
			if (visited[i])
				continue;

			dfs(i, 1);
			if (!result)
				break;
		}
		
		if (result)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
