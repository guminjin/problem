#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

struct INFO
{
	int y, x;
};

const int MAX = 1000;
const int INF = 987654321;

int n;
int arr[MAX][MAX];
int visit[MAX][MAX];

int X[4] = { 0, 0, -1, 1 };
int Y[4] = { -1, 1, 0, 0 };
int mx;
int num;

// �Ÿ�����
int dfs(INFO now)
{
	// �ش� ��ġ���� �� �� �ִ� �Ÿ�
	int &ret = visit[now.y][now.x];

	// -1�� �ƴ϶�� �̹� �Ÿ� ������ ��
	if (ret != -1)
		return ret;

	ret = 1;
	INFO next;
	// ��,��,��,�� �׹����� ��� Ȯ��
	for (int i = 0; i < 4; i++)
	{
		next.y = now.y + Y[i];
		next.x = now.x + X[i];

		// ���� Ȯ��
		if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n)
			continue;
		// ������ ��ġ���� 1ū�� Ȯ��
		if (arr[next.y][next.x] != arr[now.y][now.x] + 1)
			continue;

		ret += dfs(next);
	}

	return ret;
}


void solve()
{
	// ��� ��ġ���� �� �� �ִ� �Ÿ� 
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			// �Ÿ� ����
			int dist = dfs({ y, x });

			// �Ÿ��� mx���� ũ�ٸ� �� ����
			if (dist > mx)
			{
				mx = dist;
				num = arr[y][x];
			}
			// �Ÿ��� mx�� ����, �ش� ��ġ�� ���ȣ�� num���� �۴ٸ�
			else if (dist == mx && num > arr[y][x])
			{
				num = arr[y][x];
			}
		}
	}
}

// �Է�
void input()
{
	// �ʱ�ȭ
	memset(visit, -1, sizeof(visit));
	mx = -1;
	num = INF;

	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
			cin >> arr[y][x];
	}

}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		input();
		solve();

		cout << '#' << tc << ' ' << num << ' ' << mx << '\n';
	}
	return 0;
}
