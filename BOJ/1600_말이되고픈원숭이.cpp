#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

struct INFO
{
	int y, x;
	int move;
	int cnt;

	bool operator < (INFO now) const
	{
		return move > now.move;
	}
};

const int MAX = 200 + 1;

int garo, sero, k;
int map[MAX][MAX];
bool visit[MAX][MAX][31];
int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };

// 큐의 푸시 조건 확인
bool checkPush(INFO next)
{
	// 범위 확인
	if (next.y < 0 || next.x < 0 || next.y >= sero || next.x >= garo)
		return false;
	// 방문 확인
	if (visit[next.y][next.x][next.cnt])
		return false;
	// 해당 위치에 장애물이 있는지 확인
	if(map[next.y][next.x])
		return false;
	
	return true;
}

// bfs
int solve()
{
	// move를 기준으로 오름차순 정렬되는 우선순위 큐
	priority_queue<INFO> q;
	q.push({ 0, 0, 0, 0 });

	for (int i = 0; i < 31; i++)
		visit[0][0][i] = true;

	// 큐가 빌 때 까지 실행 => 도착지점까지 갈 수 없다.
	while (!q.empty())
	{
		INFO now = q.top(); q.pop();
		// 목적지에 도착했는지 확인
		if (now.y == sero - 1 && now.x == garo - 1)
			return now.move;

		INFO next;
		// 상, 하, 좌, 우 네 방향 확인
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];
			next.move = now.move + 1;
			next.cnt = now.cnt;
			
			// 푸시조건에 만족하면 푸시
			if (checkPush(next))
			{
				visit[next.y][next.x][next.cnt] = true;
				q.push(next);
			}
		}

		// 말의 움직임을 모두 사용했는지 확인
		if (now.cnt == k)
			continue;

		// 말이 이동할 수 있는 8가지 방법
		INFO horse[8] = { { now.y - 2, now.x - 1, now.move + 1, now.cnt + 1 }, { now.y - 2, now.x + 1, now.move + 1, now.cnt + 1 },
						  { now.y + 2, now.x - 1, now.move + 1, now.cnt + 1 }, { now.y + 2, now.x + 1, now.move + 1, now.cnt + 1 },
						  { now.y - 1, now.x - 2, now.move + 1, now.cnt + 1 }, { now.y - 1, now.x + 2, now.move + 1, now.cnt + 1 },
						  { now.y + 1, now.x - 2, now.move + 1, now.cnt + 1 }, { now.y + 1, now.x + 2, now.move + 1, now.cnt + 1 },
						};
		for (int i = 0; i < 8; i++)
		{
			next = horse[i];
			// 푸시조건에 만족하면 푸시
			if (checkPush(next))
			{
				visit[next.y][next.x][next.cnt] = true;
				q.push(next);
			}
		}
	}

	return -1;
}

// 입력
void input()
{
	cin >> k >> garo >> sero;
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

	input();
	cout << solve() << '\n';

	return 0;
}
