#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100000 + 1;	// 방의 최댓값

// 연결된 방과 길이
struct ROOM
{
	int room;
	int len;
};

struct INFO
{
	int room;
	ll len;
	ll mx;

	// len 기준으로 오름차순 정렬
	bool operator<(INFO t) const
	{
		return len > t.len;
	}
};

int n, r1, r2;			// 방의 수, 시작, 도착
vector<ROOM> m[MAX];	// 연결된 방의 정보
bool visit[MAX];		// 방문

ll bfs()
{
	priority_queue<INFO> q;
	q.push({ r1, 0, -1 });
	visit[r1] = true;

	while (!q.empty())
	{
		INFO now = q.top(); q.pop();

		// 도착치에 도착했는지 확인
		if (now.room == r2)
			return now.len - now.mx;

		int s = m[now.room].size();
		INFO next;
		// 해당 방과 연결된 모든 방을 확인
		for (int i = 0; i < s; i++)
		{
			next.room = m[now.room][i].room;
			next.len = now.len + m[now.room][i].len;
			next.mx = now.mx;

			// 방문한 방인지 확인
			if (visit[next.room])
				continue;
			// 최댓값 갱신
			if (next.mx < m[now.room][i].len)
				next.mx = m[now.room][i].len;

			// 방문처리, 큐 푸시
			visit[next.room] = true;
			q.push(next);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> r1 >> r2;

	for (int i = 0; i < n - 1; i++)
	{
		int a, b, l;
		cin >> a >> b >> l;
		m[a].push_back({ b,l });
		m[b].push_back({ a,l });
	}

	if (n == 1 || r1 == r2)
		cout << 0 << '\n';
	else
		cout << bfs() << '\n';
	return 0;
}
