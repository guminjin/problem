#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 200 + 2;

int n;
int arr[MAX];
int mxIdx;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		memset(arr, 0, sizeof(arr));

		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int a, b; cin >> a >> b;
			if (a > b)
				swap(a, b);

			// 홀수라면 1을 더해준다.
			if (a % 2 == 1)
				a++;
			if (b % 2 == 1)
				b++;

			// a, b를 절반으로 나눈 범위에 모두 1을 증가
			for(int i = a/2; i<=b/2; i++)
				arr[i]++;
		}

		int result = 0;
		// 최대값 찾기
		for (int i = 0; i < MAX; i++)
			result = max(result, arr[i]);
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}
