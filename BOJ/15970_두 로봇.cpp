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

const int MAX = 100000 + 1;	// ���� �ִ�

// ����� ��� ����
struct ROOM
{
	int room;
	int len;
};

struct INFO
{
	int room;
	ll len;
	ll mx;

	// len �������� �������� ����
	bool operator<(INFO t) const
	{
		return len > t.len;
	}
};

int n, r1, r2;			// ���� ��, ����, ����
vector<ROOM> m[MAX];	// ����� ���� ����
bool visit[MAX];		// �湮

ll bfs()
{
	priority_queue<INFO> q;
	q.push({ r1, 0, -1 });
	visit[r1] = true;

	while (!q.empty())
	{
		INFO now = q.top(); q.pop();

		// ����ġ�� �����ߴ��� Ȯ��
		if (now.room == r2)
			return now.len - now.mx;

		int s = m[now.room].size();
		INFO next;
		// �ش� ��� ����� ��� ���� Ȯ��
		for (int i = 0; i < s; i++)
		{
			next.room = m[now.room][i].room;
			next.len = now.len + m[now.room][i].len;
			next.mx = now.mx;

			// �湮�� ������ Ȯ��
			if (visit[next.room])
				continue;
			// �ִ� ����
			if (next.mx < m[now.room][i].len)
				next.mx = m[now.room][i].len;

			// �湮ó��, ť Ǫ��
			visit[next.room] = true;
			q.push(next);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> r1 >> r2;

	for (int i = 0; i < n - 1; i++)
	{
		int a, b, l;
		cin >> a >> b >> l;
		m[a].push_back({ b,l });
		m[b].push_back({ a,l });
	}

	if (n == 1 || r1 == r2)
		cout << 0 << '\n';
	else
		cout << bfs() << '\n';
	return 0;
}
