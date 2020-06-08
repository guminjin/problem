#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int max_garo = 20 + 1;
const int max_sero = 13 + 1;
const int inf = 987654321;

int garo, sero, k;
int m[max_sero][max_garo];
int mn;

bool checktest()
{
	for (int x = 0; x < garo; x++)
	{
		int flg = false;

		for (int y = 0; y < sero - k + 1; y++)
		{
			int cnt = 1;
			int cmp = m[y][x];
			for (int i = 1; i < k; i++)
			{
				if (cmp != m[y + i][x])
					break;
				cnt++;
			}
			if (cnt == k)
			{
				flg = true;
				break;
			}
		}
		if (!flg)
			return false;
	}
	return true;
}

void copyarr(int copy[max_garo], int y)
{
	for (int x = 0; x < garo; x++)
		copy[x] = m[y][x];
}
void changeoneline(int y, int ab)
{
	for (int x = 0; x < garo; x++)
		m[y][x] = ab;
}
void inputmedicine(int start, int cnt)
{
	if (cnt >= mn)
		return;

	if (start >= sero)
	{
		if (checktest())
			mn = min(cnt, mn);
		return;
	}

	// ¾È»Ñ¸±¶§
	inputmedicine(start + 1, cnt);

	int origin[max_garo];
	copyarr(origin, start);

	// a »Ñ¸±¶§
	changeoneline(start, 0);
	inputmedicine(start + 1, cnt + 1);

	// b »Ñ¸±¶§
	changeoneline(start, 1);
	inputmedicine(start + 1, cnt + 1);


	for (int x = 0; x < garo; x++)
		m[start][x] = origin[x];

}

void input()
{
	cin >> sero >> garo >> k;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> m[y][x];
		}
	}
}

void solve()
{
	mn = inf;

	input();

	bool flg = true;

	if (checktest())
		mn = 0;
	else
		inputmedicine(0, 0);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		solve();
		cout << '#' << tc << ' ' << mn << '\n';
	}
	return 0;
}
int arr[100][100];
