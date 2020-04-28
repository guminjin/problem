#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_POINT = 10000 + 1;
const int MAX_LINE = 100000 + 1;

struct POINT
{
	int cost;
	int p1, p2;

	// �������� ����
	bool operator< (POINT com)
	{
		if (cost < com.cost)
			return true;
		return false;
	}
};

int v, e;
POINT dust[MAX_LINE];	// ����� �ΰ��� ������, ����� �����ϴ� �迭
int parent[MAX_POINT];	// �θ��� ���� �迭
ll result;				// �ּ� ��� ����

// �θ�븣�� ã�´�.
int findParent(int p)
{
	if (parent[p] == p)
		return p;
	return findParent(parent[p]);
}

// �θ��带 ���� �����.
void unionParent(int p1, int p2)
{
	p1 = findParent(p1);
	p2 = findParent(p2);

	if (p1 < p2)
		parent[p2] = p1;
	else
		parent[p1] = p2;
}

// �ΰ��� ������ �θ��尡 ������ Ȯ��
bool checkParent(int p1, int p2)
{
	p1 = findParent(p1);
	p2 = findParent(p2);

	if (p1 == p2)
		return true;
	else
		return false;
}

void solve()
{
	result = 0;

	// �θ��� �ʱ�ȭ
	for (int i = 1; i <= v; i++)
		parent[i] = i;

	// ��� ���� Ȯ���Ѵ�.
	for (int i = 0; i < e; i++)
	{
		// �θ��带 Ȯ��
		if (!checkParent(dust[i].p1, dust[i].p2))
		{
			// �θ��带 ���� ���ְ�, ���� ����
			unionParent(dust[i].p1, dust[i].p2);
			result += dust[i].cost;
		}
	}
}
void input()
{
	cin >> v >> e;
	for (int i = 0; i < e; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		dust[i] = { c, a, b };
	}
	sort(dust, dust + e);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	cout << result << '\n';
	return 0;
}
