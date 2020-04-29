#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>

using namespace std;

#define endl '\n'

typedef long long ll;

int n, k;
string s;
ll hexa[7] = { pow(16, 6), pow(16, 5) , pow(16, 4) , pow(16, 3) , pow(16, 2) , pow(16, 1) , 1 };
vector<ll> v;

bool cmp(int a, int b)
{
	return a > b;
}

// 16진수->10진수
void cal(string t)
{
	// hext의 idx
	int idx = 6;

	// 10진수 변환 값
	int sum = 0;

	// t의 가장 끝부터 계산
	for (int i = t.size() - 1; i >= 0; i--)
	{
		// t[i]가 숫자일 때 num
		int num = t[i] - '0';

		// t[i]가 A~F사이일 때 num
		if (num < 0 || num > 9)
			num = t[i] - 'A' + 10;

		// 해당 자리값과 수를 곱해서 저장
		sum += num * hexa[idx--];
	}
	v.push_back(sum);
}

void solve()
{	
	// 회전가능한 수
	int turn = n / 4;

	for (int i = 0; i < turn; i++)
	{
		// 각 면을 기준으로 10진수로 계산
		for (int j = 0; j < n; j += turn)
		{
			// j번째부터 turn개의 문자를 가져온다.
			string t = s.substr(j, turn);
			// 10진수 변환
			cal(t);
		}

		// 젤앞의 문자를 끝으로 옮겨준다.
		string t = s.substr(1, n - 1);
		t += s[0];
		s = t;
	}

	// 중복제거
	sort(v.begin(), v.end(), cmp);
	v.erase(unique(v.begin(), v.end()), v.end());
}

// 입력
void input()
{
	v.clear();

	cin >> n >> k;
	cin >> s;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		input();
		solve();

		cout << "#" << t << ' ' << v[k-1] << '\n';
	}
	return 0;
}
