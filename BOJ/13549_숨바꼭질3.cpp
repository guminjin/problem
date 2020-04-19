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
int visited[MAX];

// 조건 확인
bool checkRange(INFO next)
{
	// 범위 확인
	if (next.x<0 || next.x>=MAX)
		return false;

	// 해당 위치에 도달했을때 시간확인
	if (visited[next.x] <= next.time)
		return false;

	return true;
}

void bfs()
{
	queue<INFO> q;
	q.push({ n, 0 });
	visited[n] = 0;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		if (now.x == k)
			continue;

		// x + 1, x - 1, x * 2 세가지 조건 확인
		INFO next[3] = { { now.x * 2, now.time } ,
						 { now.x + 1, now.time + 1 }, 
						 { now.x - 1, now.time + 1 }
					   };

		for (int i = 0; i < 3; i++)
		{
			if (!checkRange(next[i]))
				continue;

			// 해당 위치에 도달한 시간 저장
			visited[next[i].x] = next[i].time;
			q.push(next[i]);
		}
	}

}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	for (int i = 0; i < MAX; i++)
		visited[i] = INF;

	// 입력
	cin >> n >> k;
	bfs();
	cout << visited[k] << '\n';

	return 0;
}
