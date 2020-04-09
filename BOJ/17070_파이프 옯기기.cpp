#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 16 + 1;

struct INFO
{
	int y, x;
	int type;
};

int n;
int map[MAX][MAX];
int result;
int shape[3][3][2] = {	{{0, 1}, {0, 0}, {1, 1}},	// 파이프가 가로로 있을 때 갈수 있는 방향
						{{0, 0}, {1, 0}, {1, 1}},	// 파이프가 세로로 있을 때 갈수 있는 방향
						{{0, 1}, {1, 0}, {1, 1}}	// 파이프가 오른쪽 대각선으로 있을 때 갈수 있는 방향
					 };

void bfs()
{
	queue<INFO> q;
	q.push({ 0, 1, 0 });

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		// 배열의 오른쪽 끝에 도달하는지 체크
		if (now.x == n - 1 && now.y == n - 1)
		{
			result++;
			continue;
		}

		// 가로, 세로, 대각선 방향을 모두 확인
		for (int j = 0; j < 3; j++)
		{
			int ny = shape[now.type][j][0];
			int nx = shape[now.type][j][1];

			// nx, ny가 0이라면 해당 방향으로는 회전하고 밀 수 없다.
			if (nx == 0 && ny == 0)
				continue;

			next.y = now.y + ny;
			next.x = now.x + nx;
			next.type = j;

			// 격자판의 범위를 벗어나는지 확인
			if (next.x >= n || next.y >= n)
				continue;
			// 벽이 있다면 진행할 수 없다.
			if (map[next.y][next.x])
				continue;
			// 대각선으로 진행할 때
			if (next.type == 2)
			{	
				// 1 2 3
				// 4 5 6
				// 파이프가 1, 2에 위치할 때 2, 6으로 이동하려면
				// 3, 5, 6 위치가 모두 비어있어야 한다.
				if (map[now.y + 1][now.x] == 1 || map[now.y][now.x + 1] == 1)
					continue;
			}

			q.push(next);
		}
		
	}
}

// 입력
void input()
{
	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> map[y][x];
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
