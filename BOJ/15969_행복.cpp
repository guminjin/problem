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

const int MAX = 1000 + 1;
const int INF = 987654321;

int grade[MAX];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// 학생수 입력
	int n; cin >> n;

	int mn = INF;	// 최솟값
	int mx = -1;	// 최댓값

	for (int i = 0; i < n; i++)
	{
		// 점수 입력
		int num; cin >> num;
		if (num > mx)
			mx = num;
		if (num < mn)
			mn = num;
	}

	cout << mx - mn << '\n';
	return 0;
}
