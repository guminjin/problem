#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_GARO = 20 + 1;
const int MAX_SERO = 13 + 1;
const int INF = 987654321;

int garo, sero, k;
int m[MAX_SERO][MAX_GARO];
int mn;

bool checkTest()
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

void copyArr(int copy[MAX_GARO], int y)
{
	for (int x = 0; x < garo; x++)
		copy[x] = m[y][x];
}
void changeOneLine(int y, int ab)
{
	for (int x = 0; x < garo; x++)
		m[y][x] = ab;
}
void inputMedicine(int start, int cnt)
{
	if (cnt >= mn)
		return;

	if (start >= sero)
	{
		if (checkTest())
			mn = min(cnt, mn);
		return;
	}

	// ¾È»Ñ¸±¶§
	inputMedicine(start + 1, cnt);

	int origin[MAX_GARO];
	copyArr(origin, start);

	// A »Ñ¸±¶§
	changeOneLine(start, 0);
	inputMedicine(start + 1, cnt + 1);

	// B »Ñ¸±¶§
	changeOneLine(start, 1);
	inputMedicine(start + 1, cnt + 1);


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
	mn = INF;

	input();

	bool flg = true;

	if (checkTest())
		mn = 0;
	else
		inputMedicine(0, 0);
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
