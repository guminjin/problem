#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 50 + 1;
const int MAX_POSSIBLE = 10 + 1;

struct XY
{
	int y, x;
};

// bfs�� ���� queue����ü
struct INFO
{
	int y, x;
	int color;
	int time;
};

// garden�� ������ �������� Ȯ��
struct VISIT
{
	bool visit;
	int color;
	int time;
};

// ������ �Ѹ� �� �ִ� ��ġ�� ����
struct POSSIBLE
{
	int y, x;
	bool visit;
};

int garo, sero;
int redCnt, greenCnt;

int garden[MAX][MAX]; 
VISIT visit[MAX][MAX];

POSSIBLE possible[MAX_POSSIBLE];
int possibleCnt;

// ���� ���� ���� �� ����
int result;

XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

void print(VISIT arr[][MAX])
{
	cout << endl;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cout << arr[y][x].color << ' ';
		}
		cout << endl;
	}
}

// �ʷ�, ���� ������ ��ġ�� �����Ǿ��ٸ� ������ �۶߸���
void spreadGR()
{
	// visit�迭�� ��ȭ�� üũ
	memset(visit, 0, sizeof(visit));

	queue<INFO> q;

	// 0�ʿ� �ѷ��� ���� ��θ� queue�� Ǫ��
	// ������ �ѷ��� ��ġ�� ���� visit �迭�� ����
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (garden[y][x] == 3 || garden[y][x] == 4)
			{
				visit[y][x].color = garden[y][x];
				visit[y][x].visit = true;
				visit[y][x].time = 0;

				q.push({ y, x, garden[y][x], 0 });
			}
		}
	}

	// ���� ���� ����
	int cnt = 0;
	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		// 5��� �ʷϹ��װ� ���������� ���ÿ� ������
		// ���� �ǿ�
		if (visit[now.y][now.x].color == 5)
			continue;

		// ������ ��(�����¿�)�� ��� �۶߸�
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;
			next.time = now.time + 1;
			next.color = now.color;

			// ������ ũ�⸦ ����� �ʾƾ� ��
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;

			// ������ ȣ������ ������ �۶߸��� ����
			if (!garden[next.y][next.x])
				continue;

			// ������ �̹� ���� ��ġ���
			if (visit[next.y][next.x].visit)
			{
				// ���� �ð��� �۶߸� �������� Ȯ��
				if (visit[next.y][next.x].time == next.time)
				{
					// �̹� �ѷ��� ������ �ʷϻ��̰�, ���� �Ѹ� ������ �������̶��
					if (visit[next.y][next.x].color == 3 && next.color == 4)
					{
						// ���� �ǿ�
						visit[next.y][next.x].color = 5;
						cnt++;
					}
					// �̹� �ѷ��� ������ �������̰�, ���� �Ѹ� ������ �ʷϻ�
					if (visit[next.y][next.x].color == 4 && next.color == 3)
					{
						// ���� �ǿ�
						visit[next.y][next.x].color = 5;
						cnt++;
					}
				}
				continue;
			}

			// ������ ������ ���� ��ġ��� ������ �۶߷��ְ� queue�� Ǫ��
			visit[next.y][next.x].visit = true;
			visit[next.y][next.x].color = next.color;
			visit[next.y][next.x].time = next.time;

			q.push(next);
		}
	}

	// ���� �ִ밪�� ����
	result = max(cnt, result);
}

// ������ �ѷ��� �� �ִ� ��ġ ��
// ������ ������ ��ġ�� ����
void selectRed(int start, int cnt)
{
	if (cnt == redCnt)
	{
		spreadGR();
		return;
	}
	for (int i = start; i < possibleCnt; i++)
	{
		POSSIBLE &now = possible[i];

		if (now.visit)
			continue;

		garden[now.y][now.x] = 4;
		now.visit = true;

		selectRed(i + 1, cnt + 1);

		garden[now.y][now.x] = 2;
		now.visit = false;

	}
}

// ������ �ѷ��� �� �ִ� ��ġ ��
// �ʷϻ� ������ ��ġ�� ����
void selectGreen(int start, int cnt)
{
	if (cnt == greenCnt)
	{
		selectRed(0, 0);
		return;
	}
	for (int i = start; i < possibleCnt; i++)
	{
		POSSIBLE &now = possible[i];

		if (now.visit)
			continue;

		garden[now.y][now.x] = 3;
		now.visit = true;

		selectGreen(i + 1, cnt + 1);

		garden[now.y][now.x] = 2;
		now.visit = false;
	}
}

void solve()
{
	selectGreen(0, 0);

	cout << result << '\n';
}

// �Է�
void input()
{
	cin >> sero >> garo >> greenCnt >> redCnt;

	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> garden[y][x];

			if (garden[y][x] == 2)
			{
				possible[possibleCnt++] = { y, x, false };
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	return 0;
}
