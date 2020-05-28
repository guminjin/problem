#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

int solve(ll num)
{
	ll sum = 1;
	ll temp = 1;
	int flg = 1;
	while (sum < num)
	{
		if (flg == 1)
			temp *= 4;

		sum += temp;
		flg *= -1;
	}

	return flg;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		ll n; cin >> n;

		if (solve(n) == -1)
			cout << '#' << t << " Alice" << '\n';
		else if (solve(n) == 1)
			cout << '#' << t << " Bob" << '\n';
	}
	return 0;
}