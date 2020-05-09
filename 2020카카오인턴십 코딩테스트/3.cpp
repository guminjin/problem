#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>

using namespace std;
typedef long long ll;

const int INF = 987654321;

struct INFO
{
	int y, x;
	int dir;
	int cost;

	bool operator < (INFO now) const
	{
		return cost > now.cost;
	}
};

int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };

int solution(vector<vector<int>> board)
{
	int n = board.size();
	int visit[26][26][4];
	for (int i = 0; i < 4; i++)
	{
		for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < n; x++)
			{
				visit[y][x][i] = INF;
			}
		}
	}
	visit[0][0][0] = -500;
	visit[0][0][1] = -500;
	visit[0][0][2] = -500;
	visit[0][0][3] = -500;

	priority_queue<INFO> q;
	q.push({ 0, 0, -1, -500 });

	int result = INF;
	while (!q.empty())
	{
		INFO now = q.top(); q.pop();
		if (now.x == n - 1 && now.y == n - 1)
		{
			result = min(result, visit[now.y][now.x][now.dir]);
			continue;
		}
		if (visit[now.y][now.x][now.dir] != now.cost && now.y != 0 && now.x != 0)
			continue;

		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.y = Y[i] + now.y;
			next.x = X[i] + now.x;
			next.cost = now.cost + 100;
			next.dir = i;

			if (now.dir != next.dir)
				next.cost += 500;

			if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
				continue;
			if (board[next.y][next.x])
				continue;
			if (visit[next.y][next.x][next.dir] <= next.cost)
				continue;
			
			visit[next.y][next.x][next.dir] = next.cost;
			q.push(next);
		}
	}

	return result;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	vector<vector<int>> board = { {0,0,0},{0,0,0},{0,0,0} };
	cout << solution(board);
	return 0;
}
