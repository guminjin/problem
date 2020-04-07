#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAX = 50 + 1;
const int CHICKEN_MAX = 13 + 1;
const int HOME_MAX = MAX * 2;
const int INF = 987654321;

struct HOME
{
	int y, x;
	int dis;
};
struct XY
{
	int y, x;
};

int inning, m;
int MAP[MAX][MAX];
bool visit[MAX][MAX];
XY chicken[CHICKEN_MAX];
int chicken_cnt;
bool visit_ch[CHICKEN_MAX];
HOME home[HOME_MAX];
int home_cnt;
XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
int total_dis = INF;

void countTotalDistance()
{
	int sum = 0;
	for (int i = 0; i < home_cnt; i++)
		sum += home[i].dis;

	if (sum < total_dis)
		total_dis = sum;
}
void bfs(HOME &start)
{
	memset(visit, 0, sizeof(visit));

	queue<XY> q;
	q.push({ start.y, start.x });
	visit[start.y][start.x] = true;
	bool flg = false;
	while (!flg)
	{
		XY now = q.front(); q.pop();
		XY next;

		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + dir[i].y;
			next.x = now.x + dir[i].x;

			if (next.y<1 || next.x<1 || next.y>inning || next.x>inning)
				continue;
			if (visit[next.y][next.x])
				continue;

			if (MAP[next.y][next.x] == 1 || MAP[next.y][next.x] == 0)
			{
				q.push(next);
				visit[next.y][next.x] = true;
				continue;
			}

			if (MAP[next.y][next.x] == 2)
			{
				int idx;
				for (int i = 0; i < chicken_cnt; i++)
				{
					if (chicken[i].y == next.y && chicken[i].x == next.x)
					{
						idx = i;
						break;
					}
				}

				if (!visit_ch[idx])
				{
					q.push(next);
					visit[next.y][next.x] = true;
					continue;
				}
				else
				{
					flg = true;
					start.dis = abs(next.y - start.y) + abs(next.x - start.x);
					break;
				}
			}

		}
	}
}
void dfs(int idx, int cnt)
{
	// m개의 치킨집이 선택이 되었다면
	if (cnt == m)
	{
		for (int i = 0; i<home_cnt; i++)
			bfs(home[i]);

		countTotalDistance();
		return;
	}

	for (int i = idx; i < chicken_cnt; i++)
	{
		if (visit_ch[i])
			continue;
		visit_ch[i] = true;
		dfs(i + 1, cnt + 1);
		visit_ch[i] = false;
	}
}
void solve()
{
	// 치킨집 선택
	dfs(0, 0);
	cout << total_dis << '\n';
}
void input()
{
	cin >> inning >> m;
	for (int y = 1; y <= inning; y++)
	{
		for (int x = 1; x <= inning; x++)
		{
			int num; cin >> num;
			MAP[y][x] = num;
			if (num == 1)
				home[home_cnt++] = { y, x, 0 };
			if (num == 2)
				chicken[chicken_cnt++] = { y, x };
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