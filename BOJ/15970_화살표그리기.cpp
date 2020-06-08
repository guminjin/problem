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

const int MAX_COLOR = 5000 + 5;

// ���� ���� ��ġ
vector<int> color[MAX_COLOR];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// ���� ���� �Է�
	int n; cin >> n;
	for(int i = 0; i<n; i++)
	{
		int p, c; cin >> p >> c;
		
		// c�÷��� ���� ��ġ�� Ǫ��
		color[c].push_back(p);
	}

	ll result = 0;	// ���
	
	// ��� ���� ���� ���� Ȯ��
	for (int i = 0; i < MAX_COLOR; i++)
	{
		// ����ְų� �ش� ���� ���� ������ 0�̶��
		if (color[i].empty())
			continue;
		else if (color[i].size() == 1)
			continue;

		// �ش� ���� ���� ��ġ�� ������������ ����
		sort(color[i].begin(), color[i].end());
		int idxSize = color[i].size();	// �ش� ���� ���� ����
		for (int j = 0; j < idxSize; j++)
		{
			// ��ġ�� ���� ���� ��
			if (j == 0)
				result += color[i][j + 1] - color[i][j];
			// ��ġ�� ���� ū ��
			else if (j == idxSize - 1)
				result += color[i][j] - color[i][j - 1];
			else
			{
				int a = color[i][j + 1] - color[i][j];
				int b = color[i][j] - color[i][j - 1];
				result += min(a, b);
			}
		}
	}

	// ���
	cout << result << '\n';
	return 0;
}
