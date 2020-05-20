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

struct BC
{
	int y, x;
	int len;
	int power;
};

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

int sec, bcCnt;
vector<MAP_INFO> m[MAX][MAX];
int personA[MAX_SEC];
int personB[MAX_SEC];
BC bc[MAX_BC];
int X[5] = { 0, 0, 1, 0, -1 };
int Y[5] = { 0,-1, 0, 1, -0 };

bool visit[MAX][MAX];

int moveAB()
{
	int yA = 1, xA = 1;
	int yB = 10, xB = 10;

	int sumA = 0, sumB = 0;

	for (int i = 0; i <= sec; i++)
	{
		yA += Y[personA[i]];
		xA += X[personA[i]];

		yB += Y[personB[i]];
		xB += X[personB[i]];

		if (m[yA][xA].size() && m[yB][xB].size())
		{
			if (m[yA][xA][0].idx == m[yB][xB][0].idx)
			{
				if (m[yA][xA].size() == 1 && m[yB][xB].size() == 1)
				{
					sumA += m[yA][xA][0].power / 2;
					sumB += m[yB][xB][0].power / 2;
				}
				else if (m[yB][xB].size() == 1)
				{
					sumA += m[yA][xA][1].power;
					sumB += m[yB][xB][0].power;
				}
				else if (m[yA][xA].size() == 1)
				{
					sumA += m[yA][xA][0].power;
					sumB += m[yB][xB][1].power;
				}
				else
				{
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
			else
			{
				sumA += m[yA][xA][0].power;
				sumB += m[yB][xB][0].power;
			}

		}
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

		while (!q.empty()) 
		{
			INFO now = q.front(); q.pop();
			if (now.len >= nowBC.len)
				continue;
			for (int j = 1; j < 5; j++)
			{
				INFO next;
				next.y = now.y + Y[j];
				next.x = now.x + X[j];
				next.len = now.len + 1;

				if (next.y <= 0 || next.x <= 0 || next.y > 10 || next.x > 10)
					continue;
				if (visit[next.y][next.x])
					continue;

				m[next.y][next.x].push_back({ i, nowBC.power });
				visit[next.y][next.x] = true;
				q.push(next);
			}
		}
	}

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

void input()
{
	for (int y = 1; y < MAX; y++)
	{
		for (int x = 1; x < MAX; x++)
			m[y][x].clear();
	}

	cin >> sec >> bcCnt;

	personA[0] = personB[0] = 0;
	for (int i = 1; i <= sec; i++)
		cin >> personA[i];
	for (int i = 1; i <= sec; i++)
		cin >> personB[i];

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
