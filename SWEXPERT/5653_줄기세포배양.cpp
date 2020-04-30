#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 350 + 35;

struct XY
{
	int y, x;
};

struct VISIT
{
	int x;
	int live;	// -1이면 번식 후 비활성화
};

struct CELL
{
	int y, x;
	int live;
};

struct INFO
{
	int y, x;
	int live;
	int liveTime;
	int time;
};

int garo, sero, k;
vector<VISIT> up[MAX];
vector<VISIT> down[MAX];
vector<CELL> cell;
int result;

XY dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


int findUPIdx(XY now)
{
	int nx = now.x;
	int ny = now.y;

	int upSize = up[ny].size();
	for (int i = 0; i < upSize; i++)
	{
		if (up[ny][i].x == nx)
			return i;
	}
	return -1;
}
int findDownIdx(XY now)
{
	int nx = now.x;
	int ny = now.y * -1;

	int upSize = down[ny].size();
	for (int i = 0; i < upSize; i++)
	{
		if (down[ny][i].x == nx)
			return i;
	}
	return -1;
}
bool checkLocation(XY now, int live)
{
	if (now.y >= 0)
	{
		int idx = findUPIdx(now);
		if (up[now.y][idx].live == live)
			return true;
	}
	else
	{
		int idx = findDownIdx(now);
		if (down[now.y * -1][idx].live == live)
			return true;
	}
	return false;
}
void bfs()
{
	queue<INFO> q;
	for (int i = 0; i < cell.size(); i++)
	{
		q.push({ cell[i].y,  cell[i].x,  cell[i].live, cell[i].live, 0 });
		up[cell[i].y].push_back({ cell[i].x,  cell[i].live });
	}

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();

		// k초라면
		if (now.time == k)
		{
			while(!q.empty())
			{
				if (now.liveTime != 0)
					continue;
				if (!checkLocation({ now.y, now.x }, now.live))
					continue;

				result++;
			}
			return;
		}

		// 현재위치의 줄기세포 확인
		if (!checkLocation({ now.y, now.x }, now.live))
			continue;

		// 시간되지 않음
		if (now.liveTime != 0)
		{
			now.liveTime--;
			now.time++;
			q.push(now);
			continue;
		}
		else
		{
			// 비활성화 처리
			if (now.y >= 0)
			{
				int idx = findUPIdx({now.y, now.x});
				up[now.y][idx].live = -1;
			}
			else
			{
				int idx = findDownIdx({ now.y, now.x });
				down[now.y * -1][idx].live = -1;
			}

			for (int i = 0; i < 4; i++)
			{
				INFO next;
				next.y = now.y + dir[i].y;
				next.x = now.x + dir[i].x;
				next.live = now.live;
				next.liveTime = now.live;
				next.time = now.time + 1;

				if (next.y >= 0)
				{
					int idx = findUPIdx({ next.y, next.x });
					if (idx == -1)
						up[next.y].push_back({ next.x, next.live });
					else
					{
						if (up[next.y][idx].live == -1)
							continue;
						else if (up[next.y][idx].live >= next.live)
							continue;
						else
						{
							up[next.y][idx].live = next.live;
						}
					}
				}
				else
				{
					int idx = findDownIdx({ next.y, next.x });
					int ny = next.y * -1;
					if (idx == -1)
						down[ny].push_back({ next.x, next.live });
					else
					{
						if (down[ny][idx].live == -1)
							continue;
						else if (down[ny][idx].live >= next.live)
							continue;
						else
						{
							down[ny][idx].live = next.live;
						}
					}
				}

				q.push(next);
			}
		}
	}
}
void input()
{
	cin >> sero >> garo >> k;

	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			int n; cin >> n;

			if (n != 0)
				cell.push_back({ y, x, n});
		}
	}
}
void init()
{
	for (int i = 0; i < MAX; i++)
	{
		up[i].clear();
		down[i].clear();
	}
	cell.clear();
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		init();
		input();
		bfs();
		cout << '#' << t << ' ' << result << '\n';
	}
	return 0;
}
