#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 50 + 1;
const int MAX_POSSIBLE = 10 + 1;

struct XY
{
	int y, x;
};

// bfs를 위한 queue구조체
struct INFO
{
	int y, x;
	int color;
	int time;
};

// garden에 배양액이 퍼졌는지 확인
struct VISIT
{
	bool visit;
	int color;
	int time;
};

// 배양액을 뿌릴 수 있는 위치를 저장
struct POSSIBLE
{
	int y, x;
	bool visit;
};

int garo, sero;
int redCnt, greenCnt;

int garden[MAX][MAX]; 
VISIT visit[MAX][MAX];

POSSIBLE possible[MAX_POSSIBLE];
int possibleCnt;

// 꽃이 가장 많이 핀 개수
int result;

XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

void print(VISIT arr[][MAX])
{
	cout << endl;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cout << arr[y][x].color << ' ';
		}
		cout << endl;
	}
}

// 초록, 빨강 배양액의 위치가 지정되었다면 배양액을 퍼뜨린다
void spreadGR()
{
	// visit배열에 변화를 체크
	memset(visit, 0, sizeof(visit));

	queue<INFO> q;

	// 0초에 뿌려진 배양액 모두를 queue에 푸시
	// 배양액이 뿌려진 위치와 색을 visit 배열에 저장
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (garden[y][x] == 3 || garden[y][x] == 4)
			{
				visit[y][x].color = garden[y][x];
				visit[y][x].visit = true;
				visit[y][x].time = 0;

				q.push({ y, x, garden[y][x], 0 });
			}
		}
	}

	// 꽃의 개수 저장
	int cnt = 0;
	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		// 5라면 초록배양액과 빨간배양액이 동시에 퍼져서
		// 꽃을 피움
		if (visit[now.y][now.x].color == 5)
			continue;

		// 인접한 땅(상하좌우)에 모두 퍼뜨림
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;
			next.time = now.time + 1;
			next.color = now.color;

			// 정원의 크기를 벗어나지 않아야 함
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;

			// 정원의 호수에는 배양액을 퍼뜨릴수 없음
			if (!garden[next.y][next.x])
				continue;

			// 배양액이 이미 퍼진 위치라면
			if (visit[next.y][next.x].visit)
			{
				// 같은 시간에 퍼뜨린 배양액인지 확인
				if (visit[next.y][next.x].time == next.time)
				{
					// 이미 뿌려진 배양액이 초록색이고, 현재 뿌릴 배양액이 빨간색이라면
					if (visit[next.y][next.x].color == 3 && next.color == 4)
					{
						// 꽃을 피움
						visit[next.y][next.x].color = 5;
						cnt++;
					}
					// 이미 뿌려진 배양액이 빨간색이고, 현재 뿌릴 배양액이 초록색
					if (visit[next.y][next.x].color == 4 && next.color == 3)
					{
						// 꽃을 피움
						visit[next.y][next.x].color = 5;
						cnt++;
					}
				}
				continue;
			}

			// 배양액이 퍼지지 않은 위치라면 배양액을 퍼뜨려주고 queue에 푸시
			visit[next.y][next.x].visit = true;
			visit[next.y][next.x].color = next.color;
			visit[next.y][next.x].time = next.time;

			q.push(next);
		}
	}

	// 꽃의 최대값을 저장
	result = max(cnt, result);
}

// 배양액이 뿌려질 수 있는 위치 중
// 빨간색 배양액의 위치를 지정
void selectRed(int start, int cnt)
{
	if (cnt == redCnt)
	{
		spreadGR();
		return;
	}
	for (int i = start; i < possibleCnt; i++)
	{
		POSSIBLE &now = possible[i];

		if (now.visit)
			continue;

		garden[now.y][now.x] = 4;
		now.visit = true;

		selectRed(i + 1, cnt + 1);

		garden[now.y][now.x] = 2;
		now.visit = false;

	}
}

// 배양액이 뿌려질 수 있는 위치 중
// 초록색 배양액의 위치를 지정
void selectGreen(int start, int cnt)
{
	if (cnt == greenCnt)
	{
		selectRed(0, 0);
		return;
	}
	for (int i = start; i < possibleCnt; i++)
	{
		POSSIBLE &now = possible[i];

		if (now.visit)
			continue;

		garden[now.y][now.x] = 3;
		now.visit = true;

		selectGreen(i + 1, cnt + 1);

		garden[now.y][now.x] = 2;
		now.visit = false;
	}
}

void solve()
{
	selectGreen(0, 0);

	cout << result << '\n';
}

// 입력
void input()
{
	cin >> sero >> garo >> greenCnt >> redCnt;

	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> garden[y][x];

			if (garden[y][x] == 2)
			{
				possible[possibleCnt++] = { y, x, false };
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	return 0;
}
