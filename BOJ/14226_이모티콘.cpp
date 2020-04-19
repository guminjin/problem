#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000+ 1;

struct INFO
{
	int total, copy, sec;
};

int n;
bool time[MAX][MAX];

bool check(INFO next)
{
	if (next.total < 0 || next.copy < 0 || next.total >= MAX || next.copy >= MAX)
		return false;
	if (!next.copy || !next.total)
		return false;
	if (time[next.total][next.copy])
		return false;

	return true;
}
int bfs()
{
	queue<INFO> q;
	q.push({1, 0, 0});
	time[1][0] = true;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		if (now.total == n)
			return now.sec;
		
		INFO next[3] = { { now.total, now.total, now.sec + 1 },
						 { now.total + now.copy, now.copy, now.sec + 1 },
						 { now.total - 1, now.copy, now.sec + 1 },
						};
		for (int i = 0; i < 3; i++)
		{
			if (!check(next[i]))
				continue;

			time[next[i].total][next[i].copy] = true;
			q.push(next[i]);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n;
	cout << bfs() << '\n';
	return 0;
}
