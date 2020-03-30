#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_COMPUTER = 1000 + 1;
const int MAX_LINE = 100000;

struct COMPUTER
{
	int c1, c2;	// ���� ����� ��ǻ�� 
	int cost;	// ���� ���
	bool visit;	// �湮üũ

	// �������� ����
	bool operator<(COMPUTER com)
	{
		if (cost < com.cost)
			return true;
		return false;
	}
};

int n, m;		// ��ǻ�Ͱ���, ����� ���� ����	
ll result;		// �� ���� ���

COMPUTER computer[MAX_LINE];	// ��ǻ�� ����
int parent[MAX_LINE];			// �θ��� ���� �迭

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
		parent[b] = a;
	else
		parent[a] = b;
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

void solve()
{
	result = 0;

	// �θ��� �ʱ�ȭ
	for (int i = 1; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++)
	{
		// �θ��尡 ������ Ȯ��
		if (!checkParent(computer[i].c1, computer[i].c2))
		{
			// ��ǻ�͸� �����Ų��.
			unionParent(computer[i].c1, computer[i].c2);

			// ����� ��ǻ���� �ڽ�Ʈ�� �����ش�.
			result += computer[i].cost;
		}
	}
}

// �Է�
void input()
{
	int idx = 0;

	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		computer[i] = { a, b, c, false };
	}
	sort(computer, computer + m);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	cout << result << '\n';
	return 0;
}
