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

// ������ Ȯ��
void dfs(int idx, int cnt)
{
	// result�� true�� �̹� ���� ����
	if (result)
		return;
	
	// ���Ǹ���
	if (cnt == 4)
	{
		result = true;
		return;
	}

	// ����� ���� ã�´�.
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

// �Է�
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
	
	// ������ ������ �����غ���.
	for (int i = 0; i < n; i++)
	{
		check[i] = true;
		dfs(i, 0);
		check[i] = false;

		// resultüũ
		if (result)
		{
			cout << "1\n";
			return 0;
		}
	}
	cout << "0\n";

	return 0;
}
