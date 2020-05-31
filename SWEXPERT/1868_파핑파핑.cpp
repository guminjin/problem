#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 300 + 3;

struct XY
{
	int y, x;
};

int n;					// m�� ũ��		
char m[MAX][MAX];		// ����
int bump[MAX][MAX];		// �ֺ� ���� ���� ����
bool visit[MAX][MAX];	// �湮 �迭
vector<XY> zero;		// �ֺ� ������ ������ 0�� ��ġ ����
int result;				// ���

// ��, �Ʒ�, ����, ������, ������, ��������, ���ʾƷ�, �����ʾƷ�
int X[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
int Y[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };

// �迭 ����
void copyArr(bool origin[][MAX], bool copy[][MAX])
{
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			copy[y][x] = origin[y][x];
}

// start��ġ���� 8�������� ���� ���� Ȯ��
void bfs(XY start)
{
	queue<XY> q;
	q.push(start);
	visit[start.y][start.x] = true;

	while (!q.empty())
	{
		XY now = q.front(); q.pop();

		XY next;
		for (int i = 0; i < 8; i++)
		{
			next.y = now.y + Y[i];
			next.x = now.x + X[i];

			// ���� Ȯ��
			if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
				continue;
			// �湮 Ȯ��
			if (visit[next.y][next.x])
				continue;

			// �湮üũ
			visit[next.y][next.x] = true;
			
			// ������ ������ 0�̶�� q�� Ǫ��
			if (!bump[next.y][next.x])
				q.push({ next.y, next.x });
		}
	}

}

void solve(int zeroSize)
{
	// zero �迭�� ���鼭 ���� ���� Ȯ��
	for (int i = 0; i < zeroSize; i++)
	{
		if (visit[zero[i].y][zero[i].x])
			continue;

		bfs(zero[i]);
		result++;
	}

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (m[y][x] == '*')
				continue;
			if (!visit[y][x])
				result++;
		}
	}
}

// �ش� ��ġ���� ���������� ���� ���� ���ϱ�
void bumpCount()
{
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			// �����̶�� -1�� ����
			if (m[y][x] == '*')
			{
				bump[y][x] = -1;
				continue;
			}

			// ������ ���� ���� ����
			int cnt = 0;
			for (int i = 0; i < 8; i++)
			{
				int nx, ny;
				ny = Y[i] + y;
				nx = X[i] + x;

				if (ny < 0 || nx < 0 || ny >= n || nx >= n)
					continue;
				if (m[ny][nx] == '*')
					cnt++;
			}

			// �ֺ� ������ ������ 0�̶�� zero�迭�� ��ġ �߰�
			if (cnt == 0)
				zero.push_back({ y, x });

			// bump �迭�� ���� ����
			bump[y][x] = cnt;
		}
	}
}

// �Է�
void input()
{
	result = 0;
	zero.clear();
	memset(visit, false, sizeof(visit));

	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> m[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		input();
		bumpCount();
		int zeroSize = zero.size();
		solve(zeroSize);

		cout << '#' << t << ' ' << result << '\n';
	}
	return 0;
}
