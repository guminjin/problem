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
	int dir;
	int turn;

	// 방향전환의 횟수를 기준으로 오름차순 정렬
	bool operator <(INFO now) const
	{
		return turn > now.turn;
	}
};

int garo, sero;
char map[MAX][MAX];
int visited[MAX][MAX];
int result;

// 두개의 C의 위치
int loX[2];
int loY[2];

// 상->하->좌->우
int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };

void bfs()
{
	// cnt로 오름차순 정렬된 우선순위큐를 이용
	priority_queue<INFO> q;
	q.push({ loY[0], loX[0], -1, -1 });

	// 해당 칸에서의 방향전환의 횟수를 저장
	visited[loY[0]][loX[0]] = -1;

	while (!q.empty())
	{
		INFO now = q.top(); q.pop();

		// 다른 C를 만나면 종료
		if (now.y == loY[1] && now.x == loX[1])
		{
			result = now.turn;
			return;
		}

		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];
			next.turn = now.turn;
			next.dir = i;

			// 범위 확인
			if (next.y < 0 || next.x < 0 || next.y >= sero || next.x >= garo)
				continue;

			// 벽이면 진행할 수 없다.
			if (map[next.y][next.x] == '*')
				continue;

			// 이전의 진행하던 방향과 다르다면 방향전환 횟수 증가
			if (next.dir != now.dir)
				next.turn++;

			// 해당 위치의 방향전환 횟수가 저장되어있는 방향전환 횟수보다 큰지 확인
			if (visited[next.y][next.x] < next.turn)
				continue;

			q.push(next);
			visited[next.y][next.x] = next.turn;
		}
	}

}
void input()
{
	// visited 배열 초기화
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			visited[y][x] = INF;
		}
	}

	int idx = 0;

	// 입력
	cin >> garo >> sero;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c;

			if (c == 'C')
			{
				loY[idx] = y;
				loX[idx++] = x;
			}
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
