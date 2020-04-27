#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100000 + 1;

struct INFO
{
	int x;
	int time;
	bool operator <(INFO now) const
	{
		return time > now.time;
	}
};

int n, k;
bool visited[MAX];

int bfs()
{
	priority_queue<INFO> pq;
	pq.push({ n, 0 });
	visited[n] = true;

	while (!pq.empty())
	{
		INFO now = pq.top(); pq.pop();
		if (now.x == k)
			return now.time;

		// x + 1, x - 1, x * 2 세가지 조건 확인
		INFO next[3] = { { now.x * 2, now.time } ,
						 { now.x + 1, now.time + 1 },
						 { now.x - 1, now.time + 1 }
						};

		for (int i = 0; i < 3; i++)
		{
			if (next[i].x<0 || next[i].x >= MAX)
				continue;
			if (visited[next[i].x])
				continue;

			// 해당 위치에 도달한 시간 저장
			visited[next[i].x] = true;
			pq.push(next[i]);
		}
	}

}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// 입력
	cin >> n >> k;
	cout << bfs() << '\n';

	return 0;
}
