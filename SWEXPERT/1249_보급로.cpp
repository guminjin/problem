#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 5;
const int INF = 987654321;

struct XY
{
	int y, x;
	int time;
};

int t;
int n;
int MAP[MAX][MAX];
int visited[MAX][MAX];

XY start;
XY desination;

int X[4] = { 1, -1, 0, 0 };
int Y[4] = { 0, 0, 1, -1 };

int result;

// �ּ� �ð��� �ɸ��� ��θ� ã������ INF�� �ʱ�ȭ
void init()
{
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			visited[y][x] = INF;
		}
	}
}

// BFS
void solve()
{

	init();
	desination.y = desination.x = n - 1;
	result = INF;

	queue<XY> q;
	q.push(start);
	visited[start.y][start.x] = -1;

	while (!q.empty())
	{
		
		XY now = q.front(); q.pop();
		
		// �������� �����ϸ� �̵��ð��� üũ
		if (now.x == n - 1 && now.y == n - 1)
		{
			result = min(result, now.time);
			continue;
		}

		XY next;

		// ��ȸ�ؼ� �� �� �����Ƿ� �������� 4������ �� Ȯ��
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];
			next.time = now.time + MAP[next.y][next.x];

			// ���� üũ
			if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
				continue;

			// next.y, next.x�� �����ϴ� �������� ��� ��
			// �ּҽð��� �ɸ��� ��츸 ť�� Ǫ��
			// visited�� �ּ� �ð��� ������Ʈ
			if (next.time < visited[next.y][next.x])
			{
				visited[next.y][next.x] = next.time;
				q.push(next);
			}
		}
	}
}

// �Է�
void input()
{
	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			char c; cin >> c;

			int d = c - '0';
			MAP[y][x] = d;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		input();
		solve();
		
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}