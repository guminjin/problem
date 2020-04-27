#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 1;
const int INF = 987654321;

struct INFO
{
	int y, x;
	int cnt;

	// cnt를 기준으로 오름차순 정렬
	bool operator< (const INFO now) const
	{
		return cnt > now.cnt;
	}
};

int garo, sero; 
int map[MAX][MAX];
bool time[MAX][MAX];	// 방문 확인
int Y[4] = {0, 0, -1, 1};	// 우, 좌, 상, 하
int X[4] = {1, -1, 0, 0};	// 우, 좌, 상, 하
int result;

void bfs()
{
	// 부순 벽의 개수로 오름차순 정렬된 pq
	priority_queue<INFO> q;
	q.push({ 0, 0, 0 });
	time[0][0] = true;

	while (!q.empty())
	{
		INFO now = q.top(); q.pop();

		// 도착지에 도달했다면 
		if (now.x == garo - 1 && now.y == sero - 1)
		{
			result = now.cnt;
			return;
		}

		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + X[i];
			next.y = now.y + Y[i];
			next.cnt = now.cnt;

			// 범위확인
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			// 해당 위치에 벽이있다면 벽을 부순 수 증가
			if (map[next.y][next.x])
				next.cnt++;
			// 방문한 위치는 다시 확인하지 않는다.
			if (time[next.y][next.x])
				continue;

			q.push(next);
			time[next.y][next.x] = true;
		}
	}
}

// 입력
void input()
{
	cin >> garo >> sero;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c - '0';
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	bfs();
	cout << result << '\n';

	return 0;
}
