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

// 16����->10����
void cal(string t)
{
	// hext�� idx
	int idx = 6;

	// 10���� ��ȯ ��
	int sum = 0;

	// t�� ���� ������ ���
	for (int i = t.size() - 1; i >= 0; i--)
	{
		// t[i]�� ������ �� num
		int num = t[i] - '0';

		// t[i]�� A~F������ �� num
		if (num < 0 || num > 9)
			num = t[i] - 'A' + 10;

		// �ش� �ڸ����� ���� ���ؼ� ����
		sum += num * hexa[idx--];
	}
	v.push_back(sum);
}

void solve()
{	
	// ȸ�������� ��
	int turn = n / 4;

	for (int i = 0; i < turn; i++)
	{
		// �� ���� �������� 10������ ���
		for (int j = 0; j < n; j += turn)
		{
			// j��°���� turn���� ���ڸ� �����´�.
			string t = s.substr(j, turn);
			// 10���� ��ȯ
			cal(t);
		}

		// ������ ���ڸ� ������ �Ű��ش�.
		string t = s.substr(1, n - 1);
		t += s[0];
		s = t;
	}

	// �ߺ�����
	sort(v.begin(), v.end(), cmp);
	v.erase(unique(v.begin(), v.end()), v.end());
}

// �Է�
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
