#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 1;
const int INF = 987654321;

struct INFO
{
	int y, x;
	int cnt;

	// cnt�� �������� �������� ����
	bool operator< (const INFO now) const
	{
		return cnt > now.cnt;
	}
};

int garo, sero; 
int map[MAX][MAX];
bool time[MAX][MAX];	// �湮 Ȯ��
int Y[4] = {0, 0, -1, 1};	// ��, ��, ��, ��
int X[4] = {1, -1, 0, 0};	// ��, ��, ��, ��
int result;

void bfs()
{
	// �μ� ���� ������ �������� ���ĵ� pq
	priority_queue<INFO> q;
	q.push({ 0, 0, 0 });
	time[0][0] = true;

	while (!q.empty())
	{
		INFO now = q.top(); q.pop();

		// �������� �����ߴٸ� 
		if (now.x == garo - 1 && now.y == sero - 1)
		{
			result = now.cnt;
			return;
		}

		INFO next;
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + X[i];
			next.y = now.y + Y[i];
			next.cnt = now.cnt;

			// ����Ȯ��
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			// �ش� ��ġ�� �����ִٸ� ���� �μ� �� ����
			if (map[next.y][next.x])
				next.cnt++;
			// �湮�� ��ġ�� �ٽ� Ȯ������ �ʴ´�.
			if (time[next.y][next.x])
				continue;

			q.push(next);
			time[next.y][next.x] = true;
		}
	}
}

// �Է�
void input()
{
	cin >> garo >> sero;
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
