#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

int t;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cout << '#' << tc << ' ';
	}
	return 0;
}
