#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_N = 100 + 1;

struct DIR
{
	int sec;
	char dir;
};

struct SNAKE
{
	int y, x;
	int len;
};

int inning, appleCnt, dirCnt;
int map[MAX_N][MAX_N];
DIR dir[MAX_N];

int X[4] = { 0, 1, 0, -1 };
int Y[4] = { -1, 0, 1, 0 };

int time;

void solve()
{
	bool flg = true;
	int dirIdx = 0;
	int direction = 1;		// ó�� ������ ���������� ����

	queue<SNAKE> sn;
	sn.push({ 1, 1, 1 });
	
	while (flg)
	{
		time++;

		SNAKE now = sn.front();
		SNAKE next;
		
		next.y = now.y + Y[direction];
		next.x = now.x + X[direction];
		next.len = now.len;

		// ����������� �̵� �� ���� �������� Ȯ��
		if (next.y<1 || next.x<1 || next.y>inning || next.x>inning)
			break;

		// �ش� ��ġ�� ����� ���ٸ�
		if (!map[next.y][next.x])
		{
			sn.push(next);

			// ���� ������ ������ ������ ������ ť�� Ǫ��
			for (int i = 0; i < next.len; i++)
			{
				SNAKE ch = sn.front(); sn.pop();

				// ���� ��ġ�� �ִٸ� ���� ����� �����Ƿ� ����
				if (next.y == ch.y && next.x == ch.x)
				{
					flg = false;
					break;
				}

				// ���� ������ �����
				if (i == next.len - 1)
					break;

				sn.push(ch);
			}
		}
		// �ش� ��ġ�� ����� �ִٸ�
		else
		{
			map[next.y][next.x] = 0;
			next.len++;
			sn.push(next);

			// ���� ���̸�ŭ ť�� Ǫ��
			for (int i = 0; i < next.len - 1; i++)
			{
				SNAKE ch = sn.front(); sn.pop();

				// ���� ��ġ�� �ִٸ� ���� ����� �����Ƿ� ����
				if (next.y == ch.y && next.x == ch.x)
				{
					flg = false;
					break;
				}

				sn.push(ch);
			}
		}

		// ������ȯ
		if (dir[dirIdx].sec == time)
		{
			// ��������� �������� ��ȯ
			if (dir[dirIdx].dir == 'L')
			{
				direction = direction - 1;

				if (direction < 0)
					direction = 3;
			}
			// ��������� ���������� ��ȯ
			if (dir[dirIdx].dir == 'D')
			{
				direction = (direction + 1) % 4;
			}

			dirIdx++;
		}
	}

	// ��� ���
	cout << time << '\n';
}

// �Է�
void input()
{
	memset(map, 0, sizeof(map));

	cin >> inning >> appleCnt;
	// map�� ����� ��ġ�� 1�� �Է� 
	for (int i = 1; i <= appleCnt; i++)
	{
		int y, x; cin >> y >> x;
		map[y][x] = 1;
	}

	// ���� ���� ��ȯ ���� �Է�
	cin >> dirCnt;
	for (int i = 0; i < dirCnt; i++)
	{
		cin >> dir[i].sec >> dir[i].dir;
	}
	
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	return 0;
}
