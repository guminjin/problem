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
int total[MAX*MAX + 1];	// 나올수 있는 점수의 최대값 만큼 배열크기 설정
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
	// n가지 점수의 개수를 모두 확인
	for (int i = 0; i<inning; i++)
	{
		for (int j = sum; j >= 0; j--)
		{
			// 만들어진 점수라면 현재 점수를 더함
			if (total[j])
			{
				total[j + grade[i]] = true;
			}
		}
	}
}

// 입력
void input()
{
	cin >> inning;
	for (int x = 0; x < inning; x++)
	{
		cin >> grade[x];

		// 점수들의 최대 합은 sum
		sum += grade[x];
	}
}

// 초기화 함수
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