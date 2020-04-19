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

// start와 연결된 모든 정점을 확인
// 연결된 모든 정점의 부모를 p로 바꾼다.
void dfs(int start, int p)
{
	for (int i = 0; i < v[start].size(); i++)
	{
		int next = v[start][i];
		if (parent[next] != next)
			continue;
		parent[next] = p;
		dfs(next, p);
	}
}

void solve()
{
	int result = 0;
	
	// 모든 정점을 확인한다
	for (int i = 1; i <= n; i++)
	{
		// parent[i]확인
		// 다르면 이미 연결되어있는 정점
		if (parent[i] != i)
			continue;

		// 같으면 아직 연결이 되지않은 정점
		dfs(i, parent[i]);
		result++;
	}
	cout << result << '\n';
}

// 입력
void input()
{
	// 부모 초기화
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
