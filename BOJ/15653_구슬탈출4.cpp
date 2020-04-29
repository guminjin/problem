#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 10 + 1;

struct XY
{
	int y, x;
};

struct INFO
{
	XY r;
	XY b;
	int cnt;
};

int garo, sero;
char map[MAX][MAX];
bool visit[MAX][MAX][MAX][MAX];
XY red, blue, hole;
int result;

XY dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


void bfs()
{
	queue<INFO> q;
	q.push({ red.y, red.x, blue.y, blue.x, 0 });
	visit[red.y][red.x][blue.y][blue.x] = true;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		
		for (int i = 0; i < 4; i++)
		{
			bool flgR, flgB;
			flgR = flgB = false;

			int nyR = now.r.y;
			int nxR = now.r.x;
			int nyB = now.b.y;
			int nxB = now.b.x;
			int ncnt = now.cnt + 1;
			
			// 빨간 구슬을 i방향으로 끝까지 이동
			while (1)
			{
				nyR += dir[i].y;
				nxR += dir[i].x;

				// 벽이면
				if (map[nyR][nxR] == '#')
				{
					// i방향 반대로 한칸 돌아가고 break
					nyR -= dir[i].y;
					nxR -= dir[i].x;
					break;
				}
				// 구멍이면
				else if (map[nyR][nxR] == 'O')
				{
					// 빨간 구슬이 구멍에 빠짐
					flgR = true;
					break;
				}
			}

			// 파란 구슬을 i방향으로 끝까지 이동
			while (1)
			{
				nyB += dir[i].y;
				nxB += dir[i].x;

				// 벽이면
				if (map[nyB][nxB] == '#')
				{
					// i방향 반대로 한칸 돌아가고 break
					nyB -= dir[i].y;
					nxB -= dir[i].x;
					break;
				}
				// 구멍이면
				else if (map[nyB][nxB] == 'O')
				{
					// 파란 구슬이 구멍에 빠짐
					flgB = true;
					break;
				}
			}

			// 해당 위치가 구멍이 아니고,
			// 빨간 구슬과 파란 구슬의 위치가 같은지 확인
			if (nyR == nyB && nxR == nxB && map[nyB][nxB] != 'O')
			{
				switch (i)
				{
				case 0: // 상
					if (now.r.y > now.b.y)
						nyR++;
					else
						nyB++;
					break;
				case 1: // 하
					if (now.r.y > now.b.y)
						nyB--;
					else
						nyR--;
					break;
				case 2: // 좌
					if (now.r.x > now.b.x)
						nxR++;
					else
						nxB++;
					break;
				case 3: // 우
					if (now.r.x > now.b.x)
						nxB--;
					else
						nxR--;
					break;
				}
			}

			// 해당 위치에 방문한적 있는지 확인
			if (visit[nyR][nxR][nyB][nxB])
				continue;

			// 파란 구슬이 구멍에 빠진지 확인
			if (flgB)
				continue;
			// 파란 구슬은 구멍에 빠지지않고,
			// 빨간 구슬만 구멍에 빠졌다면
			if (flgR)
			{
				// 이동한 횟수를 result에 저장
				result = ncnt;
				// bfs 종료
				return;
			}

			// 방문 처리 후 큐에 푸시
			visit[nyR][nxR][nyB][nxB] = true;
			q.push({ nyR, nxR, nyB, nxB, ncnt });
		}
	}
}

// 입력
void input()
{
	// result 초기화
	result = -1;

	cin >> sero >> garo;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> map[y][x];

			if (map[y][x] == 'R')
				red = { y, x };
			else if (map[y][x] == 'B')
				blue = { y, x };
			else if (map[y][x] == 'O')
				hole = { y, x };
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
