#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000 + 1;

struct INFO
{
	int x, y;
	int dis;
	int wall;

	bool operator< (INFO now) const
	{
		return dis > now.dis;
	}
};

int garo, sero, k;
int map[MAX][MAX];
bool visit[11][MAX][MAX];
// ��->��->��->��
int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };

// bfs
int solve()
{
	// dis �������� �������� ����
	priority_queue<INFO> q;
	q.push({ 0, 0, 1, 0 });

	for (int i = 0; i < 11; i++)
		visit[i][0][0] = true;;

	// ť�� �������� ���� => ������ ��� ����
	while (!q.empty())
	{
		INFO now = q.top(); q.pop();

		// �������� �����ߴ��� Ȯ��
		if (now.y == sero - 1 && now.x == garo - 1)
			return now.dis;

		INFO next;
		// ��->��->��->�� �׹��� Ȯ��
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];
			next.dis = now.dis + 1;
			next.wall = now.wall;

			// ���� Ȯ��
			if (next.y < 0 | next.x < 0 || next.y >= sero || next.x >= garo)
				continue;
			// �湮 Ȯ��
			if (visit[next.wall][next.y][next.x])
				continue;
			// �ش� ������ ���̶�� ���� �μ� �� �ִ��� Ȯ��
			if (map[next.y][next.x])
			{
				// �̹� k�� �μ��ٸ� continue
				if (next.wall == k)
					continue;
				// ���� �ϳ� �μ���.
				else
					next.wall++;
			}
			
			visit[next.wall][next.y][next.x] = true;
			q.push(next);
		}
	}
	return -1;
}

// �Է�
void input()
{
	cin >> sero >> garo >> k;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c - '0';
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	priority_queue<INFO> test;
	
	input();
	cout << solve() << '\n';

	return 0;
}
