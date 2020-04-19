#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 51;

struct XY
{
	int y, x;
};

int garo, sero;
int map[MAX][MAX];
int visited[MAX][MAX];

//상하좌우, 대각선 모두 확인
XY dir[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
			 {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

// 해당 위치의 섬과 연결된 모든 섬을 찾는다.
void bfs(XY start)
{
	queue<XY> q;
	q.push(start);

	while (!q.empty())
	{
		XY now = q.front(); q.pop();
		XY next;

		for (int i = 0; i < 8; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;
			
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			if (visited[next.y][next.x] || !map[next.y][next.x])
				continue;

			visited[next.y][next.x] = true;
			q.push(next);
		}
	}
}

// 지도 입력
void input()
{
	cin >> garo >> sero;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> map[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	while (1)
	{
		// map, visited 초기화
		memset(map, 0, sizeof(map));
		memset(visited, 0, sizeof(visited));

		// 입력
		input();

		// 0, 0이 입력되면 종료
		if (garo == 0 && sero == 0)
			break;

		int result = 0;
		// 모든 위치를 확인해 본다
		for (int y = 0; y < sero; y++)
		{
			for (int x = 0; x < garo; x++)
			{
				// 방문했는 위치인지, 해당 위치가 섬인지 확인
				if (visited[y][x] || !map[y][x])
					continue;

				// 섬을 잇는다.
				bfs({ y,x });
				// 섬의 개수 증가
				result++;
			}
		}
		cout << result << '\n';
	}
	return 0;
}
