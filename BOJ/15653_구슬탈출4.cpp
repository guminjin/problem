#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 10 + 1;

struct XY
{
	int y, x;
};

struct INFO
{
	XY r;
	XY b;
	int cnt;
};

int garo, sero;
char map[MAX][MAX];
bool visit[MAX][MAX][MAX][MAX];
XY red, blue, hole;
int result;

XY dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


void bfs()
{
	queue<INFO> q;
	q.push({ red.y, red.x, blue.y, blue.x, 0 });
	visit[red.y][red.x][blue.y][blue.x] = true;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		
		for (int i = 0; i < 4; i++)
		{
			bool flgR, flgB;
			flgR = flgB = false;

			int nyR = now.r.y;
			int nxR = now.r.x;
			int nyB = now.b.y;
			int nxB = now.b.x;
			int ncnt = now.cnt + 1;
			
			// ���� ������ i�������� ������ �̵�
			while (1)
			{
				nyR += dir[i].y;
				nxR += dir[i].x;

				// ���̸�
				if (map[nyR][nxR] == '#')
				{
					// i���� �ݴ�� ��ĭ ���ư��� break
					nyR -= dir[i].y;
					nxR -= dir[i].x;
					break;
				}
				// �����̸�
				else if (map[nyR][nxR] == 'O')
				{
					// ���� ������ ���ۿ� ����
					flgR = true;
					break;
				}
			}

			// �Ķ� ������ i�������� ������ �̵�
			while (1)
			{
				nyB += dir[i].y;
				nxB += dir[i].x;

				// ���̸�
				if (map[nyB][nxB] == '#')
				{
					// i���� �ݴ�� ��ĭ ���ư��� break
					nyB -= dir[i].y;
					nxB -= dir[i].x;
					break;
				}
				// �����̸�
				else if (map[nyB][nxB] == 'O')
				{
					// �Ķ� ������ ���ۿ� ����
					flgB = true;
					break;
				}
			}

			// �ش� ��ġ�� ������ �ƴϰ�,
			// ���� ������ �Ķ� ������ ��ġ�� ������ Ȯ��
			if (nyR == nyB && nxR == nxB && map[nyB][nxB] != 'O')
			{
				switch (i)
				{
				case 0: // ��
					if (now.r.y > now.b.y)
						nyR++;
					else
						nyB++;
					break;
				case 1: // ��
					if (now.r.y > now.b.y)
						nyB--;
					else
						nyR--;
					break;
				case 2: // ��
					if (now.r.x > now.b.x)
						nxR++;
					else
						nxB++;
					break;
				case 3: // ��
					if (now.r.x > now.b.x)
						nxB--;
					else
						nxR--;
					break;
				}
			}

			// �ش� ��ġ�� �湮���� �ִ��� Ȯ��
			if (visit[nyR][nxR][nyB][nxB])
				continue;

			// �Ķ� ������ ���ۿ� ������ Ȯ��
			if (flgB)
				continue;
			// �Ķ� ������ ���ۿ� �������ʰ�,
			// ���� ������ ���ۿ� �����ٸ�
			if (flgR)
			{
				// �̵��� Ƚ���� result�� ����
				result = ncnt;
				// bfs ����
				return;
			}

			// �湮 ó�� �� ť�� Ǫ��
			visit[nyR][nxR][nyB][nxB] = true;
			q.push({ nyR, nxR, nyB, nxB, ncnt });
		}
	}
}

// �Է�
void input()
{
	// result �ʱ�ȭ
	result = -1;

	cin >> sero >> garo;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> map[y][x];

			if (map[y][x] == 'R')
				red = { y, x };
			else if (map[y][x] == 'B')
				blue = { y, x };
			else if (map[y][x] == 'O')
				hole = { y, x };
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
