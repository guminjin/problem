#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20 + 2;
const int DESSERT_MAX = 100 + 1;

struct XY
{
	int y, x;
};

int n;
int m[MAX][MAX];
bool dessert[DESSERT_MAX];

// ��, ��, ��, �� �̵�����
XY dir[4] = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };

// �̵��� �� �ִ� ��ġ���� Ȯ��
bool checkEatDessert(XY now)
{
	// x, y ���� Ȯ��
	if (now.y < 0 || now.x < 0 || now.y >= n || now.x >= n)
		return false;
	// �̹� ���� ����Ʈ���� Ȯ��
	if (dessert[m[now.y][now.x]])
		return false;

	// ���� ����Ʈ üũ
	dessert[m[now.y][now.x]] = true;
	return true;
}

// ����Ʈ ����
bool eatDessert(XY start, int garo, int sero)
{
	int idx = 0;	// �̵����� �ε���

	// �� ������ �Ʒ��� �̵�
	for (int i = 0; i < garo; i++)
	{
		start.y += dir[0].y;
		start.x += dir[0].x;

		// ��ġ ������ ����Ʈ ���� üũ
		if (!checkEatDessert(start))
			return false;
	}
	// �� ���� �Ʒ��� �̵�
	for (int i = 0; i < sero; i++)
	{
		start.y += dir[1].y;
		start.x += dir[1].x;
		if (!checkEatDessert(start))
			return false;
	}
	// �� ���� ���� �̵�
	for (int i = 0; i < garo; i++)
	{
		start.y += dir[2].y;
		start.x += dir[2].x;
		if (!checkEatDessert(start))
			return false;
	}
	// �� ������ ���� �̵�
	for (int i = 0; i < sero; i++)
	{
		start.y += dir[3].y;
		start.x += dir[3].x;
		if (!checkEatDessert(start))
			return false;
	}

	return true;
}

// �Է�
void input()
{
	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> m[y][x];
		}
	}
}

int solve()
{
	// ����� ����
	int result = -1;

	// �Է�
	input();

	// 0 �� y < n-2
	// 1 �� x < n-1
	// �ش� ������ ��ġ������ �̵��� �� ����
	for (int y = 0; y < n-2; y++)
	{
		for (int x = 1; x < n-1; x++)
		{
			memset(dessert, 0, sizeof(dessert));

			// ��, �� �̵�Ƚ�� : garo
			// ��, �� �̵�Ƚ�� : sero
			for (int garo = 1; garo < n; garo++)
			{
				for (int sero = 1; sero < n; sero++)
				{
					// dessert �迭 �ʱ�ȭ
					memset(dessert, 0, sizeof(dessert));

					// garo, sero�� ũ��� �簢���� �׸��� �ִ��� Ȯ��
					if (eatDessert({ y,x }, garo, sero))
						// �ִ밪 ����
						result = max(result, garo * 2 + sero * 2);
				}
			}
		}
	}

	return result;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		int result = solve();
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}
