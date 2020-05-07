#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

struct INFO
{
	int y, x;
	int move;
	int cnt;

	bool operator < (INFO now) const
	{
		return move > now.move;
	}
};

const int MAX = 200 + 1;

int garo, sero, k;
int map[MAX][MAX];
bool visit[MAX][MAX][31];
int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };

// ť�� Ǫ�� ���� Ȯ��
bool checkPush(INFO next)
{
	// ���� Ȯ��
	if (next.y < 0 || next.x < 0 || next.y >= sero || next.x >= garo)
		return false;
	// �湮 Ȯ��
	if (visit[next.y][next.x][next.cnt])
		return false;
	// �ش� ��ġ�� ��ֹ��� �ִ��� Ȯ��
	if(map[next.y][next.x])
		return false;
	
	return true;
}

// bfs
int solve()
{
	// move�� �������� �������� ���ĵǴ� �켱���� ť
	priority_queue<INFO> q;
	q.push({ 0, 0, 0, 0 });

	for (int i = 0; i < 31; i++)
		visit[0][0][i] = true;

	// ť�� �� �� ���� ���� => ������������ �� �� ����.
	while (!q.empty())
	{
		INFO now = q.top(); q.pop();
		// �������� �����ߴ��� Ȯ��
		if (now.y == sero - 1 && now.x == garo - 1)
			return now.move;

		INFO next;
		// ��, ��, ��, �� �� ���� Ȯ��
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];
			next.move = now.move + 1;
			next.cnt = now.cnt;
			
			// Ǫ�����ǿ� �����ϸ� Ǫ��
			if (checkPush(next))
			{
				visit[next.y][next.x][next.cnt] = true;
				q.push(next);
			}
		}

		// ���� �������� ��� ����ߴ��� Ȯ��
		if (now.cnt == k)
			continue;

		// ���� �̵��� �� �ִ� 8���� ���
		INFO horse[8] = { { now.y - 2, now.x - 1, now.move + 1, now.cnt + 1 }, { now.y - 2, now.x + 1, now.move + 1, now.cnt + 1 },
						  { now.y + 2, now.x - 1, now.move + 1, now.cnt + 1 }, { now.y + 2, now.x + 1, now.move + 1, now.cnt + 1 },
						  { now.y - 1, now.x - 2, now.move + 1, now.cnt + 1 }, { now.y - 1, now.x + 2, now.move + 1, now.cnt + 1 },
						  { now.y + 1, now.x - 2, now.move + 1, now.cnt + 1 }, { now.y + 1, now.x + 2, now.move + 1, now.cnt + 1 },
						};
		for (int i = 0; i < 8; i++)
		{
			next = horse[i];
			// Ǫ�����ǿ� �����ϸ� Ǫ��
			if (checkPush(next))
			{
				visit[next.y][next.x][next.cnt] = true;
				q.push(next);
			}
		}
	}

	return -1;
}

// �Է�
void input()
{
	cin >> k >> garo >> sero;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> map[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	cout << solve() << '\n';

	return 0;
}
