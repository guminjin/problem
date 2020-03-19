#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <set>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 4;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;	// ������ ��ġ
	int cnt;	// ���° ����
	string s;	// 0-cnt������ ��������
};

int MAP[MAX][MAX];
int t;
XY dir[4] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
set<string> s;		// �ߺ����� �ʴ� �ϰ��ڸ� ���� ����

// 4x4�� �����ǿ��� �ϰ����� ���� ����
void BFS(INFO start)
{
	queue<INFO> q;
	q.push(start);

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		// 7���� ���ڸ� ��� �����ߴٸ�
		if (now.cnt == 7)
		{
			s.insert(now.s);	// �ߺ��Ǵ� string�� insert���� ����
			continue;
		}

		// �������� ��� ������ Ȯ��
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;

			// �������� ������� Ȯ��
			if (next.x < 0 || next.y < 0 || next.x >= MAX || next.y >= MAX)
				continue;

			next.cnt = now.cnt + 1;
			next.s = now.s;
			next.s += (MAP[next.y][next.x] + '0');

			q.push(next);
		}
	}
}

void solution()
{
	s.clear();

	// ��� �������� ��ġ���� �����ؼ� 7���� ���ڸ� �������Ѵ�.
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			char s = (MAP[y][x] + '0');

			INFO t;
			t.x = x; t.y = y; t.cnt = 1; t.s = s;
			
			BFS(t);
		}
	}
}

void input()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			cin >> MAP[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	//freopen("input.txt", "r", stdin);

	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		input();
		solution();

		// set���� �ߺ�üũ�� �ϰ� insert���ֱ� ������ s�� size��ŭ ���
		cout << '#' << tc << ' ' << s.size() << '\n';
	}
	return 0;
}
