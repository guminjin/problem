#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 9;

int n;
int w[MAX];
bool visit[MAX];
int r[MAX];
int l[MAX];
int result;

void print()
{
	cout << "right : ";
	for (int i = 0; i < n; i++)
		cout << r[i] << ' ';
	cout << '\n';

	cout << "left : ";
	for (int i = 0; i < n; i++)
		cout << l[i] << ' ';
	cout << '\n';

	cout << "result : " << result << '\n';

}
void solve(int cnt)
{
	if (cnt == n)
	{
		result++;
		//print();
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (visit[i])
			continue;

		int weight = w[i];
		if (cnt == 0)
		{
			visit[i] = true;

			l[0] = weight;
			solve(cnt + 1);
			l[0] = 0;

			visit[i] = false;
		}
		else
		{
			visit[i] = true;

			r[cnt] = r[cnt - 1] + weight;
			l[cnt] = l[cnt - 1];
			if (r[cnt] <= l[cnt])
				solve(cnt + 1);
			r[cnt] = l[cnt] = 0;

			r[cnt] = r[cnt];
			l[cnt] = l[cnt - 1] + weight;
			solve(cnt + 1);
			r[cnt] = l[cnt] = 0;

			visit[i] = false;
		}
	}
}
void input()
{
	result = 0;
	memset(r, 0, sizeof(r));
	memset(l, 0, sizeof(l));
	memset(visit, 0, sizeof(visit));

	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> w[i];
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		input();
		solve(0);
		cout << '#' << t << ' ' << result << '\n';
	}
	return 0;
}
