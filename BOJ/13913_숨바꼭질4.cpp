#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100000 + 5;
const int INF = 987654321;

struct INFO
{
	int x;
	int time;
};

int n, k;
bool visited[MAX];

bool checkRange(INFO next)
{
	if (next.x<0 || next.x >= MAX)
		return false;
	if (visited[next.x])
		return false;

	return true;
}

int bfs()
{
	queue<INFO> q;
	q.push({ n, 0 });
	visited[n] = true;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		if (now.x == k)
			return now.time;
		INFO next[3] = { { now.x * 2, now.time } ,
		{ now.x + 1, now.time + 1 },
		{ now.x - 1, now.time + 1 }
		};

		for (int i = 0; i < 3; i++)
		{
			if (!checkRange(next[i]))
				continue;

			visited[next[i].x] = true;
			q.push(next[i]);
		}
	}

}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> k;
	cout << bfs() << '\n';

	return 0;
}
