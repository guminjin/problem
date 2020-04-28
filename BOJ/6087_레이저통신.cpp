#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 1;
const int INF = 987654321;

struct INFO
{
	int y, x;
	int dir;
	int turn;

	// ������ȯ�� Ƚ���� �������� �������� ����
	bool operator <(INFO now) const
	{
		return turn > now.turn;
	}
};

int garo, sero;
char map[MAX][MAX];
int visited[MAX][MAX];
int result;

// �ΰ��� C�� ��ġ
int loX[2];
int loY[2];

// ��->��->��->��
int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };

void bfs()
{
	// cnt�� �������� ���ĵ� �켱����ť�� �̿�
	priority_queue<INFO> q;
	q.push({ loY[0], loX[0], -1, -1 });

	// �ش� ĭ������ ������ȯ�� Ƚ���� ����
	visited[loY[0]][loX[0]] = -1;

	while (!q.empty())
	{
		INFO now = q.top(); q.pop();

		// �ٸ� C�� ������ ����
		if (now.y == loY[1] && now.x == loX[1])
		{
			result = now.turn;
			return;
		}

		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];
			next.turn = now.turn;
			next.dir = i;

			// ���� Ȯ��
			if (next.y < 0 || next.x < 0 || next.y >= sero || next.x >= garo)
				continue;

			// ���̸� ������ �� ����.
			if (map[next.y][next.x] == '*')
				continue;

			// ������ �����ϴ� ����� �ٸ��ٸ� ������ȯ Ƚ�� ����
			if (next.dir != now.dir)
				next.turn++;

			// �ش� ��ġ�� ������ȯ Ƚ���� ����Ǿ��ִ� ������ȯ Ƚ������ ū�� Ȯ��
			if (visited[next.y][next.x] < next.turn)
				continue;

			q.push(next);
			visited[next.y][next.x] = next.turn;
		}
	}

}
void input()
{
	// visited �迭 �ʱ�ȭ
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			visited[y][x] = INF;
		}
	}

	int idx = 0;

	// �Է�
	cin >> garo >> sero;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c;

			if (c == 'C')
			{
				loY[idx] = y;
				loX[idx++] = x;
			}
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
