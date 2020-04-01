#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20 + 1;	

int n;
int map[MAX][MAX];
int mx;

// �迭�� ����
void copyMap(int origin[][MAX], int copy[][MAX])
{
	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			copy[y][x] = origin[y][x];
		}
	}
}

// �ִ밪 ã��
void maxValue()
{
	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			if (mx < map[y][x])
				mx = map[y][x];
		}
	}
}

// ���̿� �ִ� 0�� ������ �ش�
void removeZero()
{
	int temp[MAX][MAX];
	memset(temp, 0, sizeof(temp));
	for (int x = 1; x <= n; x++)
	{
		int idx = 1;
		for (int y = 1; y <= n; y++)
		{
			if (!map[y][x])
				continue;
			temp[idx++][x] = map[y][x];
		}
	}

	copyMap(temp, map);
}

// ���� �̵��ϰ�, �����ش�
void moveUp()
{
	removeZero();

	for (int x = 1; x <= n; x++)
	{
		for (int y = 1; y <= n; y++)
		{
			if (y >= n)
				break;
			if (map[y][x] != map[y + 1][x])
				continue;

			map[y][x] += map[y + 1][x];
			map[y + 1][x] = 0;
		}
	}

	removeZero();
}

// 90�� ȸ�����ش�.
void rotate()
{
	int temp[MAX][MAX];

	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			temp[y][x] = map[n - x + 1][y];
		}
	}

	copyMap(temp, map);
}

// ��� ����� ���� ��� �غ���.
void dfs(int cnt)
{
	// 5�� �̵��ߴٸ� �ִ밪�� Ȯ��
	if (cnt == 5)
	{
		maxValue();
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int temp[MAX][MAX];
		copyMap(map, temp);

		moveUp();
		dfs(cnt + 1);

		copyMap(temp, map);
		rotate();
	}
}

// �Է�
void input()
{
	cin >> n;
	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			cin >> map[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	dfs(0);
	cout << mx << '\n';
	return 0;
}
