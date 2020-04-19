#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20000 + 1;

int n, m;
vector<int> v[MAX];
int color[MAX];
bool result;

// start정점에 연결된 모든 정점 확인
void dfs(int start, int c)
{
	color[start] = c;
	for (int i = 0; i < v[start].size(); i++)
	{
		int next = v[start][i];
		
		// 이미 다른 정점과 연결되어 있다면
		if (color[next])
		{
			// 각 정점의 색을 확인
			// 색이 같다면 이분 그래프가 아니다.
			if (color[next] == color[start])
			{
				result = false;
				return;
			}
			continue;
		}
		// 연결되어 있지않다면 해당 정점도 순회
		else
		{
			dfs(next, c *-1);
			if (!result)
				return;
		}
	}
}

// 입력
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
	
	// 테스트케이스 입력
	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		// v와 color, result 초기화
		for (int i = 0; i < MAX; i++)
		{
			v[i].clear();
			color[i] = 0;
		}
		result = true;

		// 입력
		input();
		
		// 모든 정점을 확인
		for (int i = 1; i <= n; i++)
		{
			// 0이 아니라면 이미 연결된 정점
			if (color[i])
				continue;

			// 연결되지 않은 정점에 대해 확인
			dfs(i, 1);

			// result가 false라면, 이분그래프가 아님
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
