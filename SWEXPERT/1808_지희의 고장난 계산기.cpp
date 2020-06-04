#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 1000000 + 1;
const int INF = 987654321;

bool number[10];
int x;
int xLen;

bool datas[MAX];

int mn = INF;

bool checkPossible(int n)
{
	string s = to_string(n);
	int sLen = s.length();
	for (int i = 0; i < sLen; i++)
	{
		if (!number[(s[i]-'0')])
			return false;
	}
	
	return true;
}

void divNum(int num, int result)
{
	if (num == 1)
	{
		mn = min(mn, result);
		return;
	}
	for (int i = num; i > 1; i--)
	{
		if (!datas[i])
			continue;

		if(num % i == 0)
			divNum(num / i, result + (to_string(i).length()) + 1);
	}
}
void makeNum(int cnt, int num)
{
	if (cnt >= xLen)
	{
		return;
	}
	for (int i = 0; i < 10; i++)
	{
		if (!number[i])
			continue;

		int now = (num * 10) + i;
		
		if (x < now)
			return;
		

		datas[now] = true;
		makeNum(cnt + 1, now);
	}
}
void input()
{
	for (int i = 0; i < 10; i++)
		cin >> number[i];
	
	cin >> x;
	xLen = to_string(x).length();
}

void solve()
{
	mn = INF;
	input();

	// x를 입력할 수 있는지 확인
	if (checkPossible(x))
	{
		string s = to_string(x);
		mn = s.length() + 1;
		return;
	}

	// 사용할 수 있는 숫자로 만들수 있는 수
	memset(datas, 0, sizeof(datas));
	makeNum(0, 0);
	divNum(x, 0);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		solve();
		if (mn == INF)
			mn = -1;
		cout << '#' << tc << ' ' << mn << '\n';
	}
	return 0;
}
