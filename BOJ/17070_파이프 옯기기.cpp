#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 16 + 1;

struct INFO
{
	int y, x;
	int type;
};

int n;
int map[MAX][MAX];
int result;
int shape[3][3][2] = {	{{0, 1}, {0, 0}, {1, 1}},	// �������� ���η� ���� �� ���� �ִ� ����
						{{0, 0}, {1, 0}, {1, 1}},	// �������� ���η� ���� �� ���� �ִ� ����
						{{0, 1}, {1, 0}, {1, 1}}	// �������� ������ �밢������ ���� �� ���� �ִ� ����
					 };

void bfs()
{
	queue<INFO> q;
	q.push({ 0, 1, 0 });

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		// �迭�� ������ ���� �����ϴ��� üũ
		if (now.x == n - 1 && now.y == n - 1)
		{
			result++;
			continue;
		}

		// ����, ����, �밢�� ������ ��� Ȯ��
		for (int j = 0; j < 3; j++)
		{
			int ny = shape[now.type][j][0];
			int nx = shape[now.type][j][1];

			// nx, ny�� 0�̶�� �ش� �������δ� ȸ���ϰ� �� �� ����.
			if (nx == 0 && ny == 0)
				continue;

			next.y = now.y + ny;
			next.x = now.x + nx;
			next.type = j;

			// �������� ������ ������� Ȯ��
			if (next.x >= n || next.y >= n)
				continue;
			// ���� �ִٸ� ������ �� ����.
			if (map[next.y][next.x])
				continue;
			// �밢������ ������ ��
			if (next.type == 2)
			{	
				// 1 2 3
				// 4 5 6
				// �������� 1, 2�� ��ġ�� �� 2, 6���� �̵��Ϸ���
				// 3, 5, 6 ��ġ�� ��� ����־�� �Ѵ�.
				if (map[now.y + 1][now.x] == 1 || map[now.y][now.x + 1] == 1)
					continue;
			}

			q.push(next);
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
			cin >> map[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	bfs();
	cout << result << '\n';
	return 0;
}
