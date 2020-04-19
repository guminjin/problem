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

// start������ ����� ��� ���� Ȯ��
void dfs(int start, int c)
{
	color[start] = c;
	for (int i = 0; i < v[start].size(); i++)
	{
		int next = v[start][i];
		
		// �̹� �ٸ� ������ ����Ǿ� �ִٸ�
		if (color[next])
		{
			// �� ������ ���� Ȯ��
			// ���� ���ٸ� �̺� �׷����� �ƴϴ�.
			if (color[next] == color[start])
			{
				result = false;
				return;
			}
			continue;
		}
		// ����Ǿ� �����ʴٸ� �ش� ������ ��ȸ
		else
		{
			dfs(next, c *-1);
			if (!result)
				return;
		}
	}
}

// �Է�
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
	
	// �׽�Ʈ���̽� �Է�
	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		// v�� color, result �ʱ�ȭ
		for (int i = 0; i < MAX; i++)
		{
			v[i].clear();
			color[i] = 0;
		}
		result = true;

		// �Է�
		input();
		
		// ��� ������ Ȯ��
		for (int i = 1; i <= n; i++)
		{
			// 0�� �ƴ϶�� �̹� ����� ����
			if (color[i])
				continue;

			// ������� ���� ������ ���� Ȯ��
			dfs(i, 1);

			// result�� false���, �̺б׷����� �ƴ�
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
