#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100;

int t;
int inning;
int result;
int grade[MAX];
int total[MAX*MAX + 1];	// ���ü� �ִ� ������ �ִ밪 ��ŭ �迭ũ�� ����
int sum;

void cnt()
{
	result = 0;
	for (int i = 0; i < MAX*MAX + 1; i++)
	{
		if (total[i])
			result++;
	}
}

void solve()
{
	// n���� ������ ������ ��� Ȯ��
	for (int i = 0; i<inning; i++)
	{
		for (int j = sum; j >= 0; j--)
		{
			// ������� ������� ���� ������ ����
			if (total[j])
			{
				total[j + grade[i]] = true;
			}
		}
	}
}

// �Է�
void input()
{
	cin >> inning;
	for (int x = 0; x < inning; x++)
	{
		cin >> grade[x];

		// �������� �ִ� ���� sum
		sum += grade[x];
	}
}

// �ʱ�ȭ �Լ�
void init()
{
	memset(grade, 0, sizeof(grade));
	memset(total, 0, sizeof(total));
	total[0] = true;
	sum = 0;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		init();
		input();
		solve();
		cnt();
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}