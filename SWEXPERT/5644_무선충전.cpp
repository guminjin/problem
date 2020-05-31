#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <cstring>
using namespace std;

#define endl '\n'
typedef long long ll;

const int MAX = 10 + 1;
const int MAX_SEC = 100 + 1;
const int MAX_BC = 8 + 1;

// BC�� �߽� ��ġ, ����, ����
struct BC
{
	int y, x;
	int len;
	int power;
};

// m�� ����
struct MAP_INFO
{
	int idx;
	int power;

	bool operator< (MAP_INFO m) const
	{
		return power > m.power;
	}
};

struct INFO
{
	int y, x;
	int len;
};

int sec, bcCnt;					// ��, BC�� ����
vector<MAP_INFO> m[MAX][MAX];	// ����	
int personA[MAX_SEC];			// A�� �̵����
int personB[MAX_SEC];			// B�� �̵����
BC bc[MAX_BC];					// ������ BC�� ����

int X[5] = { 0, 0, 1, 0, -1 };	// 1:��, 2:��, 3:��, 4:�� 
int Y[5] = { 0,-1, 0, 1, -0 };

bool visit[MAX][MAX];			// �湮 Ȯ��

int moveAB()
{
	// A�� B�� ������ġ �ʱ�ȭ
	int yA = 1, xA = 1;
	int yB = 10, xB = 10;

	// ������
	int sumA = 0, sumB = 0;

	// sec�� ���� �̵�
	for (int i = 0; i <= sec; i++)
	{
		yA += Y[personA[i]];
		xA += X[personA[i]];

		yB += Y[personB[i]];
		xB += X[personB[i]];

		// A�� B�� ��ġ���� �迭�� ũ�Ⱑ �� �� 0�� �ƴ� ��
		if (m[yA][xA].size() && m[yB][xB].size())
		{
			// �ش� ��ġ�� 0��° �迭���� BC�� idx�� ���� ��
			if (m[yA][xA][0].idx == m[yB][xB][0].idx)
			{
				// A, B ��ġ�� �迭�� ũ�Ⱑ 1�̶��
				// ���� BC�� �����ϹǷ� power / 2�� ������ �������� ���Ѵ�.
				if (m[yA][xA].size() == 1 && m[yB][xB].size() == 1)
				{
					sumA += m[yA][xA][0].power / 2;
					sumB += m[yB][xB][0].power / 2;
				}

				// B�� ��ġ�� �迭�� ũ�Ⱑ 1�̶��
				// B�� ���������� �ش� ��ġ�� 0��° �ε����� power�� ���ϰ�,
				// A�� ���������� �ش� ��ġ�� 1��° �ε����� power�� ���Ѵ�.
				else if (m[yB][xB].size() == 1)
				{
					sumA += m[yA][xA][1].power;
					sumB += m[yB][xB][0].power;
				}

				// A�� ��ġ�� �迭�� ũ�Ⱑ 1�̶��
				// A�� ���������� �ش� ��ġ�� 0��° �ε����� power�� ���ϰ�,
				// B�� ���������� �ش� ��ġ�� 1��° �ε����� power�� ���Ѵ�.
				else if (m[yA][xA].size() == 1)
				{
					sumA += m[yA][xA][0].power;
					sumB += m[yB][xB][1].power;
				}

				// A, B��ġ�� �迭�� ũ�Ⱑ ��� 2�̻��̶��
				else
				{
					// 1��° �ε����� power�� ���ؼ� ������ power�� ���Ѵ�.
					if (m[yA][xA][1].power >= m[yB][xB][1].power)
					{
						sumA += m[yA][xA][1].power;
						sumB += m[yB][xB][0].power;
					}
					else if (m[yA][xA][1].power < m[yB][xB][1].power)
					{
						sumA += m[yA][xA][0].power;
						sumB += m[yB][xB][1].power;
					}
				}
			}

			// �ش� ��ġ�� 0��° �迭���� BC�� idx�� �ٸ� ��
			else
			{
				sumA += m[yA][xA][0].power;
				sumB += m[yB][xB][0].power;
			}

		}

		// A�� B�� ��ġ���� �迭�� ũ�Ⱑ 0�� ��
		else
		{
			if (m[yA][xA].size())
			{
				sumA += m[yA][xA][0].power;
			}
			if (m[yB][xB].size())
			{
				sumB += m[yB][xB][0].power;
			}
		}
	}
	return sumA + sumB;
}

// ������ BC�� �߽ɿ��� ���� ã��
void bfs()
{
	for (int i = 1; i <= bcCnt; i++)
	{
		BC nowBC = bc[i];

		queue<INFO> q;
		q.push({ nowBC.y, nowBC.x, 0 });
		m[nowBC.y][nowBC.x].push_back({ i, nowBC.power });

		memset(visit, 0, sizeof(visit));
		visit[nowBC.y][nowBC.x] = true;

		// BC[i]�� ������ �ִ� ���� ã��
		while (!q.empty()) 
		{
			INFO now = q.front(); q.pop();

			// ���� Ȯ��
			if (now.len >= nowBC.len)
				continue;

			// ��, ��, ��, �� �׹��� ��� Ȯ��
			for (int j = 1; j < 5; j++)
			{
				INFO next;
				next.y = now.y + Y[j];
				next.x = now.x + X[j];
				next.len = now.len + 1;

				// ���� üũ
				if (next.y <= 0 || next.x <= 0 || next.y > 10 || next.x > 10)
					continue;
				// �湮 üũ
				if (visit[next.y][next.x])
					continue;

				// m�� BC�� ��ȣ�� power Ǫ��
				m[next.y][next.x].push_back({ i, nowBC.power });
				// �湮 ó��
				visit[next.y][next.x] = true;
				q.push(next);
			}
		}
	}

	// m�� power�� �������� �������� ����
	for (int y = 1; y < MAX; y++)
	{
		for (int x = 1; x < MAX; x++)
		{
			if (!m[y][x].size())
				continue;
			else
				sort(m[y][x].begin(), m[y][x].end());
		}
	}
}

// �Է�
void input()
{
	for (int y = 1; y < MAX; y++)
	{
		for (int x = 1; x < MAX; x++)
			m[y][x].clear();
	}

	cin >> sec >> bcCnt;

	// ��� ��ġ�� 0�� ���� ������ ����
	personA[0] = personB[0] = 0;
	for (int i = 1; i <= sec; i++)
		cin >> personA[i];
	for (int i = 1; i <= sec; i++)
		cin >> personB[i];

	// BC�� ���� �Է�
	for (int i = 1; i <= bcCnt; i++)
	{
		int y, x, length, power;
		cin >> x >> y >> length >> power;
		bc[i] = { y, x, length, power };
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		input();
		bfs();
		cout << '#' << t << ' ' << moveAB() << '\n';
	}
	return 0;
}