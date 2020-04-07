#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAX_sero = 15 + 1;
const int MAX_garo = 12 + 1;
const int INF = 987654321;

struct XY
{
	int y, x;
};

int tc;
int inning, garo, sero;
int brick[MAX_sero][MAX_garo];
int visited[MAX_sero][MAX_garo];
XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
int mnBricks;

void copy(int arr[][MAX_garo], int copy[][MAX_garo])
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			copy[y][x] = arr[y][x];
		}
	}
}

void print(int arr[][MAX_garo])
{
	cout << endl;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cout << arr[y][x] << ' ';
		}
		cout << endl;
	}
}

// ������ ��� ���ŵǾ����� Ȯ��
bool check()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (brick[y][x])
				return false;
		}
	}
	return true;
}

// ���� ������ �� ����
void countBrick()
{
	int sum = 0;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (!brick[y][x])
				continue;

			sum++;
		}
	}
	if (sum < mnBricks)
		mnBricks = sum;
	//cout << "sum : " << sum << ", mn : " << mnBricks << endl;
}

// ������ �Ʒ��� ����
void dropBrick()
{
	int temp[MAX_sero][MAX_garo];
	memset(temp, 0, sizeof(temp));

	int copyY;
	for (int x = 0; x < garo; x++)
	{
		// ���� �Ʒ����� �׾ư�
		copyY = sero - 1;
		for (int y = sero - 1; y >= 0; y--)
		{
			// ���� �����̳�, �ش� ��ġ�� 0�̸� ���� ����
			if (!brick[y][x] || visited[y][x])
				continue;

			temp[copyY--][x] = brick[y][x];
		}
	}
	copy(temp, brick);
}

// �ش� ��ġ�� (���� - 1) ��ŭ �����¿��� ������ ���߸�
void breakBrick(XY now, bool flg)
{
	int cnt = brick[now.y][now.x] - 1;
	visited[now.y][now.x] = flg;

	if (cnt)
	{
		for (int i = 0; i < 4; i++)
		{
			XY next = now;
			for (int j = 0; j < cnt; j++)
			{
				next.x += dir[i].x;
				next.y += dir[i].y;

				if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
					continue;

				if (visited[next.y][next.x] == flg)
					continue;

				visited[next.y][next.x] = flg;

				// ũ�Ⱑ 1�̸� �ڱ��ڽŸ� ���߸��� ��
				if (brick[next.y][next.x] == 1)
					continue;

				breakBrick(next, flg);
			}
		}
	}
}

// �� ������ ���� �� ����
// ������ �Ʒ��� ����
void dfs(XY xy, int cnt)
{
	if (cnt == inning)
	{
		countBrick();
		return;
	}

	// N�� �ȿ� ��� ������ ���ŵǾ��ٸ�
	if (!mnBricks || check())
		return;

	for (int x = 0; x < garo; x++)
	{
		int copyBrick[MAX_sero][MAX_garo];
		for (int y = 0; y < sero; y++)
		{
			if (!brick[y][x])
				continue;
			if (brick[y - 1][x])
				break;
			//cout << "\ncnt : " << cnt << ", y : " << y << " x : " << x << endl;

			copy(brick, copyBrick);
			memset(visited, 0, sizeof(visited));
			breakBrick({ y, x }, true);

			//print(brick);
			dropBrick();

			//print(brick);
			dfs({ y, x }, cnt + 1);
			copy(copyBrick, brick);
		}
	}
}

void solve(int i)
{
	mnBricks = INF;
	dfs({ 0, 0 }, 0);
	cout << '#' << i + 1 << ' ' << mnBricks << '\n';

}

// �Է�
void input()
{
	cin >> inning >> garo >> sero;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
			cin >> brick[y][x];
	}
	countBrick();
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	//freopen("in.txt", "r", stdin);

	cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		input();
		solve(t);
	}

	return 0;
}