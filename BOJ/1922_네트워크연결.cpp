#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_COMPUTER = 1000 + 1;
const int MAX_LINE = 100000;

struct LOCATION
{
	int c1, c2;
};

struct COMPUTER
{
	int c1, c2;	// ���� ����� ��ǻ�� 
	int cost;	// ���� ���
	bool visit;	// �湮üũ
};

int n, m;		// ��ǻ�Ͱ���, ����� ���� ����	
ll result;		// �� ���� ���

COMPUTER computer[MAX_LINE];	// ��ǻ�� ����

int cost[MAX_LINE];			// �������� ������������ ����
int parent[MAX_LINE];		// �θ��� ���� �迭

// origin�� �θ����� ��� ��ǻ�͸� change�� �θ�� �ٲ۴�.
void changeParent(int origin, int change)
{
	for (int i = 1; i <= m; i++)
	{
		if (parent[i] == origin)
			parent[i] = change;
	}
}

// �θ��� ã��
int findParent(int a)
{
	if (parent[a] == a)
		return a;
	return findParent(parent[a]);
}

// �θ��� ��ġ��
void unionParent(int a, int b)
{
	a = findParent(a);
	b = findParent(b);

	// �� �� �θ��尡 ���� �ɷ� �θ��� ����
	if (a < b)
	{
		parent[b] = a;
		changeParent(b, a);
	}
	else
	{
		parent[a] = b;
		changeParent(a, b);
	}
}

// �θ��尡 ������ Ȯ��
bool checkParent(int a, int b)
{
	a = findParent(a);
	b = findParent(b);

	if (a == b)
		return true;
	else
		return false;
}

// �� ���� ��ǻ�Ͱ� ����Ǿ����� Ȯ��
bool checkConnection()
{
	for (int i = 1; i < n; i++)
	{
		if (parent[i] != parent[i + 1])
			return false;
	}
	return true;
}

// �ش� �ڽ�Ʈ�� ��ǻ���� ��ȣ�� ��ȯ
LOCATION findComputer(int ncost)
{
	for (int i = 0; i < m; i++)
	{
		// ������ �� ��ǻ�ʹ� �����ʴ´�.
		if (computer[i].visit)
			continue;

		if (computer[i].cost == ncost)
		{
			computer[i].visit = true;
			return { computer[i].c1, computer[i].c2 };
		}
	}
	return { -1, -1 };
}


void solve()
{
	result = 0;

	// �θ��� �ʱ�ȭ
	for (int i = 1; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++)
	{
		// �� ���� ��ǻ�Ͱ� ����Ǿ����� Ȯ��
		if (checkConnection())
			break;

		int ncost = cost[i];
		LOCATION lo = findComputer(ncost);
		
		// -1�� �̹� ����Ǿ��� ��ǻ���̴�.
		if (lo.c1 == -1 || lo.c2 == -1)
			continue;

		// �θ��尡 ������ Ȯ��
		if (checkParent(lo.c1, lo.c2))
			continue;

		// ��ǻ�͸� �����Ų��.
		unionParent(lo.c1, lo.c2);

		// ����� ��ǻ���� �ڽ�Ʈ�� �����ش�.
		result += ncost;
	}
}

// �Է�
void input()
{
	int idx = 0;

	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		computer[idx] = { a, b, c, false };
		cost[idx++] = c;
	}

	sort(cost, cost + idx);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	cout << result << '\n';
	return 0;
}
