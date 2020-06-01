#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20;
const int INF = 987654321;

int n, b;
int person[MAX];
int mn; 

// DFS
void go(int now, int sum)
{
	if (now > n)
		return;
	if (sum >= b)
	{
		mn = min(mn, sum);
	}

	// �ش� �ε����� ���� ���ų�, ���� �ʰų�
	go(now + 1, sum + person[now]);
	go(now + 1, sum);
}

// �Է�
void input()
{
	mn = INF;

	cin >> n >> b;
	for (int i = 0; i < n; i++)
		cin >> person[i];	
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		input();
		go(0, 0);
		cout << '#' << tc << ' ' << mn - b << '\n';
	}
	return 0;
}
