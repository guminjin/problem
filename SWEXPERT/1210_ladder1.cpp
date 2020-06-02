#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100;
const int INF = 987654321;

struct XY
{
	int y, x;
};

int arr[MAX][MAX];
bool visit[MAX][MAX];
XY des;

int bfs(XY start)
{
	// visit 배열 초기화
	memset(visit, 0, sizeof(visit));

	queue<XY> q;
	q.push(start);
	visit[start.y][start.x] = true;

	while (!q.empty())
	{
		XY now = q.front(); q.pop();

		// y = 99이면 도착
		if (now.y == 0)
			return now.x;
		

		// 좌, 우로 갈 수 있는지 확인 후 아래로 진행
		int temp[3][2] = { { now.y, now.x - 1 },
						   { now.y, now.x + 1 },
						   { now.y - 1, now.x }
						};

		// 좌, 우, 아래
		for (int i = 0; i < 3; i++)
		{
			int ny = temp[i][0];
			int nx = temp[i][1];

			// x의 범위 확인
			if (nx < 0 || nx >= MAX)
				continue;
			// 방문 확인
			if (visit[ny][nx])
				continue;
			// 해당 위치가 0인지 확인
			if (!arr[ny][nx])
				continue;

			// 방문 처리
			visit[ny][nx] = true;
			q.push({ ny, nx });
			break;
		}
	}
}

// 입력
void input()
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			cin >> arr[y][x];
			
		}
	}

	// 2가 위치한 x, y 찾기
	for (int x = 0; x < MAX; x++)
	{
		if (arr[99][x] == 2)
		{
			des.y = 99;
			des.x = x;
			break;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	for (int tc = 1; tc <= 10; tc++)
	{
		int t; cin >> t;
		input();
		cout << '#' << tc << ' ' << bfs( des ) << '\n';
	}
	return 0;
}
