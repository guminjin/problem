#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100;
const int INF = 987654321;

struct XY
{
	int y, x;
	int cnt;
};

int arr[MAX][MAX];
bool visit[MAX][MAX];

int bfs(XY start)
{
	// visit �迭 �ʱ�ȭ
	memset(visit, 0, sizeof(visit));

	queue<XY> q;
	q.push(start);
	visit[start.y][start.x] = true;

	while (1)
	{
		XY now = q.front(); q.pop();
		
		// y = 99�̸� ����
		if (now.y == 99)
		{
			return now.cnt;
		}

		// ��, ��� �� �� �ִ��� Ȯ�� �� �Ʒ��� ����
		int temp[3][2] = { { now.y, now.x - 1 },
						   { now.y, now.x + 1 },
						   { now.y + 1, now.x } 
						};

		// ��, ��, �Ʒ�
		for (int i = 0; i < 3; i++)
		{
			int ny = temp[i][0];
			int nx = temp[i][1];

			// x�� ���� Ȯ��
			if (nx < 0 || nx >= MAX)
				continue;
			// �湮 Ȯ��
			if (visit[ny][nx])
				continue;
			// �ش� ��ġ�� 0���� Ȯ��
			if (!arr[ny][nx])
				continue;

			// �湮 ó��
			visit[ny][nx] = true;
			q.push({ ny, nx, now.cnt + 1 });
			break;
		}
	}
}

int solve()
{	
	int mn = INF;	// �Ÿ� �ּҰ�
	int idx;		// �Ÿ� �ּҰ��� �ε���

	// y = 0�� ��, �ش� ��ġ�� 1�̸� bfs�� ���� 
	for (int x = 0; x < MAX; x++)
	{
		// �ش� ��ġ�� 0���� Ȯ��
		if (!arr[0][x])
			continue;

		// �Ÿ� ����
		int dist = bfs({ 0, x , 0});

		// mn���� �Ÿ��� ���ų� ������ �� ����
		if (dist <= mn)
		{
			mn = dist;
			idx = x;
		}
	}

	return idx;
}

// �Է�
void input()
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			cin >> arr[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	for (int tc = 1; tc <= 10; tc++)
	{
		int t; cin >> t;
		input();
		cout << '#' << tc << ' ' << solve() << '\n';
	}
	return 0;
}
