#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 50 + 1;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;
	int type;
	int time;
};

int garo, sero;
char map[MAX][MAX];
int visited[MAX][MAX];
XY dir[4] = { { 0, 1 },{ 0, -1 },{ 1, 0 },{ -1, 0 } };
XY cleaner;
vector<XY> water;

int bfs()
{
	queue<INFO> q;

	// 물의 위치를 먼저 큐에 넣고, 고슴도치의 위치를 큐에 넣어준다.
	// type이 0이면 물, 1이면 고슴도치
	for (int i = 0; i < water.size(); i++)
		q.push({ water[i].y, water[i].x, 0, 0 });
	q.push({ cleaner.y, cleaner.x, 1, 0 });
	
	visited[cleaner.y][cleaner.x] = true;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		// 고슴도치일 때 
		if (now.type)
		{
			// 목적지에 도착했는지 체크
			if (map[now.y][now.x] == 'D')
				return now.time;
	
			// 우,좌,하,상 네방향을 모두 확인
			for (int i = 0; i < 4; i++)
			{
				next.x = now.x + dir[i].x;
				next.y = now.y + dir[i].y;
				next.type = 1;
				next.time = now.time + 1;

				// 범위확인
				if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
					continue;
				// 물이거나 돌인지 확인
				if (map[next.y][next.x] == '*' || map[next.y][next.x] == 'X')
					continue;
				// 방문한 위치인지 확인
				if (visited[next.y][next.x])
					continue;
				
				visited[next.y][next.x] = true;
				q.push(next);
			}
		}
		// 물일 때
		else
		{
			// 우,좌,하,상 네방향을 모두 확인
			for (int i = 0; i < 4; i++)
			{
				next.x = now.x + dir[i].x;
				next.y = now.y + dir[i].y;
				next.type = 0;
				next.time = now.time + 1;

				// 범위 확인
				if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
					continue;
				// 이미 물이 차있거나, 돌인지, 도착지이면 물이 퍼질 수 없다.
				if (map[next.y][next.x] == '*' || map[next.y][next.x] == 'X' || map[next.y][next.x] == 'D')
					continue;

				map[next.y][next.x] = '*';
				q.push(next);
			}
		}
	}
	return -1;
}

// 입력
void input()
{
	cin >> sero >> garo;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c;

			// 시작위치 저장
			if (c == 'S')
			{
				cleaner.y = y;
				cleaner.x = x;
			}
			// 물이 차있는 지역 저장
			else if (c == '*')
			{
				water.push_back({ y, x });
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	int result = bfs();
	if (result != -1)
		cout << result << '\n';
	else
		cout << "KAKTUS\n";

	return 0;
}
