#include <iostream>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 10000 + 1;
const int INF = ((1 << 31) - 1);

int k, n;
ll arr[MAX];
ll mx =0;
ll result;

bool check(ll mid) {
	int sum = 0;
	for (int i = 0; i < k; i++) {
		sum += (arr[i] / mid);
	}
	return sum >= n;
}

void binarySearch() {
	ll start = 1;
	ll end = mx;

	while (start<=end) {
		ll mid = (start + end) / 2;

		if (check(mid)) {
			if (result < mid) result = mid;
			start = mid + 1;
		}
		else end = mid - 1;

	}

}
void input() {
	cin >> k >> n;
	for (int i = 0; i < k; i++) {
		cin >> arr[i];
		if (arr[i] > mx) {
			mx = arr[i];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	input();
	binarySearch();
	cout << result << '\n';
	return 0;
}
