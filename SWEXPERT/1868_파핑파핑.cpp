#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 300 + 3;

struct XY
{
	int y, x;
};

int n;					// m의 크기		
char m[MAX][MAX];		// 지도
int bump[MAX][MAX];		// 주변 지뢰 개수 저장
bool visit[MAX][MAX];	// 방문 배열
vector<XY> zero;		// 주변 지뢰의 개수가 0인 위치 저장
int result;				// 결과

// 위, 아래, 왼쪽, 오른쪽, 왼쪽위, 오른쪽위, 왼쪽아래, 오른쪽아래
int X[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
int Y[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };

// 배열 복사
void copyArr(bool origin[][MAX], bool copy[][MAX])
{
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			copy[y][x] = origin[y][x];
}

// start위치부터 8방향으로 지뢰 개수 확인
void bfs(XY start)
{
	queue<XY> q;
	q.push(start);
	visit[start.y][start.x] = true;

	while (!q.empty())
	{
		XY now = q.front(); q.pop();

		XY next;
		for (int i = 0; i < 8; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];

			// 범위 확인
			if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
				continue;
			// 방문 확인
			if (visit[next.y][next.x])
				continue;

			// 방문체크
			visit[next.y][next.x] = true;
			
			// 지뢰의 개수가 0이라면 q에 푸시
			if (!bump[next.y][next.x])
				q.push({ next.y, next.x });
		}
	}

}

void solve(int zeroSize)
{
	// zero 배열을 돌면서 지뢰 개수 확인
	for (int i = 0; i < zeroSize; i++)
	{
		if (visit[zero[i].y][zero[i].x])
			continue;

		bfs(zero[i]);
		result++;
	}

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (m[y][x] == '*')
				continue;
			if (!visit[y][x])
				result++;
		}
	}
}

// 해당 위치에서 여덟방향의 지뢰 개수 구하기
void bumpCount()
{
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			// 지뢰이라면 -1을 저장
			if (m[y][x] == '*')
			{
				bump[y][x] = -1;
				continue;
			}

			// 주위의 지뢰 개수 저장
			int cnt = 0;
			for (int i = 0; i < 8; i++)
			{
				int nx, ny;
				ny = Y[i] + y;
				nx = X[i] + x;

				if (ny < 0 || nx < 0 || ny >= n || nx >= n)
					continue;
				if (m[ny][nx] == '*')
					cnt++;
			}

			// 주변 지뢰의 개수가 0이라면 zero배열에 위치 추가
			if (cnt == 0)
				zero.push_back({ y, x });

			// bump 배열에 개수 저장
			bump[y][x] = cnt;
		}
	}
}

// 입력
void input()
{
	result = 0;
	zero.clear();
	memset(visit, false, sizeof(visit));

	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> m[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		input();
		bumpCount();
		int zeroSize = zero.size();
		solve(zeroSize);

		cout << '#' << t << ' ' << result << '\n';
	}
	return 0;
}
