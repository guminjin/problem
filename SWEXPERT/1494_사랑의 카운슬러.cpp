#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20;

struct XY
{
	int y, x;
};

int n;
XY bug[MAX];
int order[MAX];

void dfs(int now)
{

}

void input()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y; cin >> x >> y;
		bug[i] = { y,x };
	}
}
void solve()
{
	for (int i = 0; i < MAX; i++)
		order[i] = i;

	input();

	do {
		int xDist[2][10];
		int yDist[2][10];
		for (int i = 0; i < MAX; i += 2)
		{
			XY a = bug[order[i]];
			XY b = bug[order[i + 1]];
			
			int xd = a.x - b.x;
			int yd = a.y - b.y;

			xDist[0][i / 2] = xd;
			yDist[0][i / 2] = yd;

			xDist[1][i / 2] = -xd;
			yDist[1][i / 2] = -yd;
		}
	} while (next_permutation(order, order + n));
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cout << '#' << tc << ' ';
	}
	return 0;
}
