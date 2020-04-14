#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 2000;

int n, m;
vector<int> connect[MAX];
bool check[MAX];
bool result = false;

// 연결점 확인
void dfs(int idx, int cnt)
{
	// result가 true면 이미 조건 만족
	if (result)
		return;
	
	// 조건만족
	if (cnt == 4)
	{
		result = true;
		return;
	}

	// 연결된 점을 찾는다.
	for (int i = 0; i < connect[idx].size(); i++)
	{
		int now = connect[idx][i];
		if (check[now])
			continue;

		check[now] = true;
		dfs(now, cnt + 1);
		check[now] = false;
		
		if (result)
			return;
	}
	
}

// 입력
void input()
{
	memset(check, 0, sizeof(check));

	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		connect[a].push_back(b);
		connect[b].push_back(a);
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	
	// 각각의 점에서 시작해본다.
	for (int i = 0; i < n; i++)
	{
		check[i] = true;
		dfs(i, 0);
		check[i] = false;

		// result체크
		if (result)
		{
			cout << "1\n";
			return 0;
		}
	}
	cout << "0\n";

	return 0;
}
