#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20 + 1;
const int INF = 987654321;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;
	int mem;
	int dir;
};

int t;
int n;
int garo, sero;
char program[MAX][MAX];
bool visited[MAX][MAX][16];
bool direction[MAX][MAX][4];

XY dir[4] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };

void nextLocation(INFO now, INFO &next, int idx)
{
	next.y = (now.y + dir[idx].y) % sero;
	next.x = (now.x + dir[idx].x) % garo;
	
	// x�� y�� -1�� ��
	if (next.y == -1)
		next.y = sero - 1;
	if (next.x == -1)
		next.x = garo - 1;
	next.mem = now.mem;
	next.dir = idx;
}

vector<INFO> oper(INFO now)
{
	vector<INFO> v;
	char ch = program[now.y][now.x];
	INFO next;

	// ����
	if (ch >= '0' && '9' >= ch)
	{
		nextLocation(now, next, now.dir);
		next.mem = (ch - '0');
		v.push_back(next);
		
		return v;
	}

	// ����
	switch (ch)
	{
	case '<':
		nextLocation(now, next, 0);
		v.push_back(next);
		break;
	case '>':
		nextLocation(now, next, 1);
		v.push_back(next); 
		break;
	case '^':
		nextLocation(now, next, 2);
		v.push_back(next);
		break;
	case 'v':
		nextLocation(now, next, 3);
		v.push_back(next);
		break;

	case '_':
		if (!now.mem)
		{
			nextLocation(now, next, 1);
			v.push_back(next);
		}
		else
		{
			nextLocation(now, next, 0);
			v.push_back(next);
		}
		break;
	case '|':
		if (!now.mem)
		{
			nextLocation(now, next, 3);
			v.push_back(next);
		}
		else
		{
			nextLocation(now, next, 2);
			v.push_back(next);
		}
		break;

	case '?':
		for (int i = 0; i < 4; i++)
		{
			nextLocation(now, next, i);
			v.push_back(next);
		}
		break;
	case '.':
		nextLocation(now, next, now.dir);
		v.push_back(next);
		break;

	case '@':
		next.mem = INF;
		v.push_back(next);
		break;

	case '+':
		nextLocation(now, next, now.dir);
		
		// �޸� + 1�� 16�̸� 0
		next.mem = (now.mem + 1) % 16;
		v.push_back(next);
		break;
	case '-':
		nextLocation(now, next, now.dir);
		next.mem = (now.mem - 1);

		// �޸𸮰� - 1�� -1�̸� 15
		if (next.mem == -1)
			next.mem = 15;
		v.push_back(next);
		break;
	}

	return v;
}

bool bfs(INFO start)
{
	queue<INFO> q;
	q.push(start);

	visited[start.y][start.y][start.mem] = true;
	direction[start.y][start.y][start.dir] = true;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		vector<INFO> next = oper(now);
		
		for (int i = 0; i < next.size(); i++)
		{
			INFO t = next[i];

			if (t.mem == INF)
				return true;

			// Ư�� ��ġ�� ���� �� �޸𸮿� ������ ��쵵 Ǫ���ϸ� ���� �ݺ��ǹǷ� continue��
			if (visited[t.y][t.x][t.mem] && direction[t.y][t.x][t.dir])
				continue;

			visited[t.y][t.x][t.mem] = true;
			direction[t.y][t.x][t.dir] = true;

			q.push(t);
		}
	}
	return false;
}

bool solve()
{
	char ch = program[0][0];

	// 0,0 ��ġ�� 0~9 ���̶�� �޸𸮿� �ش� ���ڸ� ����
	if (ch >= '0' && '9' >= ch)
		return bfs({ 0, 0, ch - '0', 1 });
	// ���ڶ�� �޸𸮴� 0
	else		
		return bfs({ 0, 0, 0, 1 });
}

// �Է�
void input()
{
	cin >> sero >> garo;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			char c; cin >> c;
			program[y][x] = c;
		}
	}
}

// �ʱ�ȭ
void init()
{
	memset(program, 0, sizeof(program));
	memset(visited, 0, sizeof(visited));
	memset(direction, 0, sizeof(direction));
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		init();
		input();

		int flg = solve();

		if (flg)
			cout << '#' << tc << " YES\n";
		else
			cout << '#' << tc << " NO\n";

	}
	return 0;
}
