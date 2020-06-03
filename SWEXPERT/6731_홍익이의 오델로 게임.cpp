#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000 + 10;

int n;
char arr[MAX][MAX];
int garo[MAX];
int sero[MAX];

int solve()
{
	// ���� Ƚ��
	int result = 0;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			int blackStone = garo[x] + sero[y];
			if (arr[y][x] == 'B')
				blackStone--;

			if (blackStone % 2)
				result++;
		}
	}
	return result;
}
void input()
{
	memset(garo, 0, sizeof(garo));
	memset(sero, 0, sizeof(sero));

	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> arr[y][x];

			// �������̸� ����, ���� �迭�� 1����
			if (arr[y][x] == 'B')
			{
				garo[x]++;
				sero[y]++;
			}
		}
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
		cout << '#' << tc << ' '<<solve() << '\n';
	}
	return 0;
}
