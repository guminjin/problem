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

// 조건 확인
bool check(INFO next)
{
	// 범위 확인
	if (next.total < 0 || next.copy < 0 || next.total >= MAX || next.copy >= MAX)
		return false;

	// 스티커 수나 클립보드의 스티커 수가 0인지 확인
	if (!next.copy || !next.total)
		return false;

	// 이미 확인한 조건인지 확인
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
		
		// 복사, 붙여넣기, 하나 삭제 세가지 경우
		INFO next[3] = { { now.total, now.total, now.sec + 1 },
						 { now.total + now.copy, now.copy, now.sec + 1 },
						 { now.total - 1, now.copy, now.sec + 1 },
						};
		for (int i = 0; i < 3; i++)
		{
			if (!check(next[i]))
				continue;

			// 해당 조건 확인
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
