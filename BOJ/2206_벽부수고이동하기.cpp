#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000 + 1;
const int INF = 987654321;

struct INFO
{
	int y, x;
	int time;
	int turn;

	// time�� �������� �������� ����
	bool operator <(INFO now) const
	{
		return time > now.time;
	}
};

int garo, sero;
bool map[MAX][MAX];
bool visited[2][MAX][MAX];
int result = -1;

// ��, ��, ��, ��
int Y[4] = { 0, 0, -1, 1 };
int X[4] = { 1, -1, 0, 0 }; 

void bfs()
{
	memset(visited, 0, sizeof(visited));

	priority_queue<INFO> pq;
	pq.push({ 0, 0, 1, 0 });

	visited[0][0][0] = visited[1][0][0] = true;

	while (!pq.empty())
	{
		INFO now = pq.top(); pq.pop();
		
		// ������ ���޽� ����
		if (now.x == garo - 1 && now.y == sero - 1)
		{
			result = now.time;
			return;
		}

		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + X[i];
			next.y = now.y + Y[i];
			next.time = now.time + 1;
			next.turn = now.turn;

			// ���� Ȯ��
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			// �湮�� �迭 üũ
			if (visited[next.turn][next.y][next.x])
				continue;
			// ���� �μ� �� �ִ��� Ȯ��
			if (map[next.y][next.x] && next.turn)
				continue;
			// ���� �μ� �� �ִٸ�
			if (map[next.y][next.x] && !next.turn)
			{
				// ���� �μ� �� ����
				next.turn++;
				// ���� �μ��� �� ���� ��ġ �湮 üũ
				visited[next.turn][next.y][next.x] = true;

				pq.push(next);
				continue;
			}
			
			visited[next.turn][next.y][next.x] = true;
			pq.push(next);
		}
	}
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
			map[y][x] = c - '0';
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
