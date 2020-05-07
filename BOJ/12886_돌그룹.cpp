#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

// a, b, c�� �ִ밪 
const int MAX = 500 + 1;

struct INFO
{
	int a, b, c;
};

int a, b, c;
int result = -1;
int visit[MAX][MAX];

// ������ ���� �������ش�.
// a < b < c
void valueCompare(int &a, int &b, int &c)
{
	// �ּڰ�
	int mn = min(a, min(b, c));
	// �ִ밪
	int mx = max(a, max(b, c));
	// �߰���
	int mid = a + b + c - mn - mx;

	a = mn;
	b = mid;
	c = mx;
}

// bfs
int solve()
{
	queue<INFO> q;
	q.push({ a, b, c });

	// a, b, c ����
	valueCompare(a, b, c);
	// �湮ó��
	visit[a][b] = true;

	// q�� ������� ���� => ���� ���� ���� �� ����.
	while (!q.empty())
	{
		INFO now = q.front(); q.pop();

		// a = b = c��� ����
		if (now.a == now.b && now.b == now.c)
			return 1;

		// a, b, c�� ���� �� �ִ� ������ ����� ��
		INFO next[3] = { {now.a*2, now.b, now.c- now.a},
						 { now.a*2, now.b- now.a, now.c},
						 { now.a, now.b*2, now.c- now.b}
						};

		for (int i = 0; i < 3; i++)
		{
			INFO n = next[i];
			// ����
			valueCompare(n.a, n.b, n.c);

			// �湮Ȯ��
			if (visit[n.a][n.b])
				continue;

			// �湮ó�� �� ť�� Ǫ��
			visit[n.a][n.b] = true;
			q.push(n);
		}
	}
	return 0;
}

// �Է�
void input()
{
	int sum = 0;
	cin >> a >> b >> c;
	sum = a + b + c;

	// sum�� 3���� ����������� ������
	// a, b, c�� ��� ���� ���� �� �� ����.
	if (sum % 3 == 0)
		result = 0;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();

	// 3���� ����������� ����
	if (result == -1)
		cout << "0\n";
	else
		cout << solve() << '\n';
	
	return 0;
}
