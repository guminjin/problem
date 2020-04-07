#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'
typedef long long ll;

const int MAX_DAY = 15 + 1;

struct INFO
{
	int time;
	int pay;
};

int inning;
INFO day[MAX_DAY];
int mx;

void func1(int idx, int value)
{	
	INFO now = day[idx];
	int nextIdx = idx + now.time;
	
	if (nextIdx > inning)
	{
		// in time, consult can finish
		if (nextIdx - 1 == inning)
			value += day[idx].pay;

		mx = max(mx, value);
		return;
	}
	for (int i = nextIdx - 1; i <= inning; i++)
	{
		func1(i + 1, value + now.pay);
	}	
}
void solution()
{
	for (int i = 1; i <= inning; i++)
		func1(i, 0);

	cout << mx << '\n';
}
void input()
{
	cin >> inning;
	for (int i = 1; i <= inning; i++)
	{
		INFO t;
		cin >> t.time >> t.pay;

		day[i] = t;
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solution();
	
	return 0;
}
