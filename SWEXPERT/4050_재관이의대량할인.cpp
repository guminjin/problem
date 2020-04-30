#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100000 + 10;

int arr[MAX];

bool cmp(int a, int b)
{
	return a > b;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		for (int x = 0; x < MAX; x++)
			arr[x] = 0;

		int result = 0;
		int n; cin >> n;
		for (int i = 0; i < n; i++)
			cin >> arr[i];
		
		sort(arr, arr + n, cmp);

		int div = n / 3;
		for (int i = 0; i < div*3; i += 3)
		{
			int mn = min(arr[i], min(arr[i + 1], arr[i + 2]));
			int sum = arr[i] + arr[i + 1] + arr[i + 2];
			sum -= mn;
			result += sum;
		}
		for (int i = div*3; i < n; i++)
			result += arr[i];

		cout << '#' << t << ' ' << result << '\n';
	}
	return 0;
}
