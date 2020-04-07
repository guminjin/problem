#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAX_sero = 15 + 1;
const int MAX_garo = 12 + 1;
const int INF = 987654321;

struct XY
{
	int y, x;
};

int tc;
int inning, garo, sero;
int brick[MAX_sero][MAX_garo];
int visited[MAX_sero][MAX_garo];
XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
int mnBricks;

void copy(int arr[][MAX_garo], int copy[][MAX_garo])
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			copy[y][x] = arr[y][x];
		}
	}
}

void print(int arr[][MAX_garo])
{
	cout << endl;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cout << arr[y][x] << ' ';
		}
		cout << endl;
	}
}

// 벽돌이 모두 제거되었는지 확인
bool check()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (brick[y][x])
				return false;
		}
	}
	return true;
}

// 남은 벽돌의 수 세기
void countBrick()
{
	int sum = 0;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (!brick[y][x])
				continue;

			sum++;
		}
	}
	if (sum < mnBricks)
		mnBricks = sum;
	//cout << "sum : " << sum << ", mn : " << mnBricks << endl;
}

// 벽돌을 아래로 내림
void dropBrick()
{
	int temp[MAX_sero][MAX_garo];
	memset(temp, 0, sizeof(temp));

	int copyY;
	for (int x = 0; x < garo; x++)
	{
		// 제일 아래부터 쌓아감
		copyY = sero - 1;
		for (int y = sero - 1; y >= 0; y--)
		{
			// 깨진 벽돌이나, 해당 위치가 0이면 쌓지 않음
			if (!brick[y][x] || visited[y][x])
				continue;

			temp[copyY--][x] = brick[y][x];
		}
	}
	copy(temp, brick);
}

// 해당 위치의 (숫자 - 1) 만큼 상하좌우의 벽돌을 깨뜨림
void breakBrick(XY now, bool flg)
{
	int cnt = brick[now.y][now.x] - 1;
	visited[now.y][now.x] = flg;

	if (cnt)
	{
		for (int i = 0; i < 4; i++)
		{
			XY next = now;
			for (int j = 0; j < cnt; j++)
			{
				next.x += dir[i].x;
				next.y += dir[i].y;

				if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
					continue;

				if (visited[next.y][next.x] == flg)
					continue;

				visited[next.y][next.x] = flg;

				// 크기가 1이면 자기자신만 깨뜨리면 됨
				if (brick[next.y][next.x] == 1)
					continue;

				breakBrick(next, flg);
			}
		}
	}
}

// 깰 벽돌을 선택 후 제거
// 벽돌을 아래로 내림
void dfs(XY xy, int cnt)
{
	if (cnt == inning)
	{
		countBrick();
		return;
	}

	// N번 안에 모든 벽돌이 제거되었다면
	if (!mnBricks || check())
		return;

	for (int x = 0; x < garo; x++)
	{
		int copyBrick[MAX_sero][MAX_garo];
		for (int y = 0; y < sero; y++)
		{
			if (!brick[y][x])
				continue;
			if (brick[y - 1][x])
				break;
			//cout << "\ncnt : " << cnt << ", y : " << y << " x : " << x << endl;

			copy(brick, copyBrick);
			memset(visited, 0, sizeof(visited));
			breakBrick({ y, x }, true);

			//print(brick);
			dropBrick();

			//print(brick);
			dfs({ y, x }, cnt + 1);
			copy(copyBrick, brick);
		}
	}
}

void solve(int i)
{
	mnBricks = INF;
	dfs({ 0, 0 }, 0);
	cout << '#' << i + 1 << ' ' << mnBricks << '\n';

}

// 입력
void input()
{
	cin >> inning >> garo >> sero;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
			cin >> brick[y][x];
	}
	countBrick();
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	//freopen("in.txt", "r", stdin);

	cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		input();
		solve(t);
	}

	return 0;
}