#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <set>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 4;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;	// 숫자의 위치
	int cnt;	// 몇번째 숫자
	string s;	// 0-cnt까지의 숫자저장
};

int MAP[MAX][MAX];
int t;
XY dir[4] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
set<string> s;		// 중복되지 않는 일곱자리 숫자 받음

// 4x4의 격자판에서 일곱개의 숫자 선택
void BFS(INFO start)
{
	queue<INFO> q;
	q.push(start);

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		// 7개의 숫자를 모두 선택했다면
		if (now.cnt == 7)
		{
			s.insert(now.s);	// 중복되는 string은 insert하지 않음
			continue;
		}

		// 동서남북 모든 방향을 확인
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;

			// 격자판을 벗어나는지 확인
			if (next.x < 0 || next.y < 0 || next.x >= MAX || next.y >= MAX)
				continue;

			next.cnt = now.cnt + 1;
			next.s = now.s;
			next.s += (MAP[next.y][next.x] + '0');

			q.push(next);
		}
	}
}

void solution()
{
	s.clear();

	// 모든 격자판의 위치에서 시작해서 7개의 숫자를 만들어야한다.
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			char s = (MAP[y][x] + '0');

			INFO t;
			t.x = x; t.y = y; t.cnt = 1; t.s = s;
			
			BFS(t);
		}
	}
}

void input()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			cin >> MAP[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	//freopen("input.txt", "r", stdin);

	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		input();
		solution();

		// set에서 중복체크를 하고 insert해주기 때문에 s의 size만큼 출력
		cout << '#' << tc << ' ' << s.size() << '\n';
	}
	return 0;
}
