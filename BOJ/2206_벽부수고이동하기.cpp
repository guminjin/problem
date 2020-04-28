#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000 + 1;
const int INF = 987654321;

struct INFO
{
	int y, x;
	int time;
	int turn;

	// time을 기준으로 오름차순 정렬
	bool operator <(INFO now) const
	{
		return time > now.time;
	}
};

int garo, sero;
bool map[MAX][MAX];
bool visited[2][MAX][MAX];
int result = -1;

// 우, 좌, 상, 하
int Y[4] = { 0, 0, -1, 1 };
int X[4] = { 1, -1, 0, 0 }; 

void bfs()
{
	memset(visited, 0, sizeof(visited));

	priority_queue<INFO> pq;
	pq.push({ 0, 0, 1, 0 });

	visited[0][0][0] = visited[1][0][0] = true;

	while (!pq.empty())
	{
		INFO now = pq.top(); pq.pop();
		
		// 목적지 도달시 종료
		if (now.x == garo - 1 && now.y == sero - 1)
		{
			result = now.time;
			return;
		}

		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + X[i];
			next.y = now.y + Y[i];
			next.time = now.time + 1;
			next.turn = now.turn;

			// 범위 확인
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			// 방문한 배열 체크
			if (visited[next.turn][next.y][next.x])
				continue;
			// 벽을 부술 수 있는지 확인
			if (map[next.y][next.x] && next.turn)
				continue;
			// 벽을 부술 수 있다면
			if (map[next.y][next.x] && !next.turn)
			{
				// 벽을 부순 수 증가
				next.turn++;
				// 벽을 부수고 난 후의 위치 방문 체크
				visited[next.turn][next.y][next.x] = true;

				pq.push(next);
				continue;
			}
			
			visited[next.turn][next.y][next.x] = true;
			pq.push(next);
		}
	}
}

// 입력
void input()
{
	cin >> sero >> garo;
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
