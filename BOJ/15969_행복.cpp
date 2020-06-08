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

	// �л��� �Է�
	int n; cin >> n;

	int mn = INF;	// �ּڰ�
	int mx = -1;	// �ִ�

	for (int i = 0; i < n; i++)
	{
		// ���� �Է�
		int num; cin >> num;
		if (num > mx)
			mx = num;
		if (num < mn)
			mn = num;
	}

	cout << mx - mn << '\n';
	return 0;
}
