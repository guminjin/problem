#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_N = 100 + 1;

struct DIR
{
	int sec;
	char dir;
};

struct SNAKE
{
	int y, x;
	int len;
};

int inning, appleCnt, dirCnt;
int map[MAX_N][MAX_N];
DIR dir[MAX_N];

int X[4] = { 0, 1, 0, -1 };
int Y[4] = { -1, 0, 1, 0 };

int time;

void solve()
{
	bool flg = true;
	int dirIdx = 0;
	int direction = 1;		// 처음 방향은 오른쪽으로 진행

	queue<SNAKE> sn;
	sn.push({ 1, 1, 1 });
	
	while (flg)
	{
		time++;

		SNAKE now = sn.front();
		SNAKE next;
		
		next.y = now.y + Y[direction];
		next.x = now.x + X[direction];
		next.len = now.len;

		// 진행방향으로 이동 후 벽을 만났는지 확인
		if (next.y<1 || next.x<1 || next.y>inning || next.x>inning)
			break;

		// 해당 위치에 사과과 없다면
		if (!map[next.y][next.x])
		{
			sn.push(next);

			// 뱀의 꼬리를 제외한 나머지 몸통을 큐에 푸시
			for (int i = 0; i < next.len; i++)
			{
				SNAKE ch = sn.front(); sn.pop();

				// 같은 위치가 있다면 뱀의 몸통과 만나므로 멈춤
				if (next.y == ch.y && next.x == ch.x)
				{
					flg = false;
					break;
				}

				// 뱀의 꼬리를 지운다
				if (i == next.len - 1)
					break;

				sn.push(ch);
			}
		}
		// 해당 위치에 사과가 있다면
		else
		{
			map[next.y][next.x] = 0;
			next.len++;
			sn.push(next);

			// 뱀의 길이만큼 큐에 푸시
			for (int i = 0; i < next.len - 1; i++)
			{
				SNAKE ch = sn.front(); sn.pop();

				// 같은 위치가 있다면 뱀의 몸통과 만나므로 멈춤
				if (next.y == ch.y && next.x == ch.x)
				{
					flg = false;
					break;
				}

				sn.push(ch);
			}
		}

		// 방향전환
		if (dir[dirIdx].sec == time)
		{
			// 진행방향의 왼쪽으로 전환
			if (dir[dirIdx].dir == 'L')
			{
				direction = direction - 1;

				if (direction < 0)
					direction = 3;
			}
			// 진행방향의 오른쪽으로 전환
			if (dir[dirIdx].dir == 'D')
			{
				direction = (direction + 1) % 4;
			}

			dirIdx++;
		}
	}

	// 결과 출력
	cout << time << '\n';
}

// 입력
void input()
{
	memset(map, 0, sizeof(map));

	cin >> inning >> appleCnt;
	// map의 사과의 위치에 1을 입력 
	for (int i = 1; i <= appleCnt; i++)
	{
		int y, x; cin >> y >> x;
		map[y][x] = 1;
	}

	// 뱀의 방향 전환 정보 입력
	cin >> dirCnt;
	for (int i = 0; i < dirCnt; i++)
	{
		cin >> dir[i].sec >> dir[i].dir;
	}
	
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	return 0;
}
