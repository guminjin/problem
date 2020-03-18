#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 11;
const int INF = 987654321;

int n;
int number[MAX];
int oper[4];			// +, -, *, / count
int cal[MAX - 1];		// each operation
bool visited[MAX - 1];	

int mn = INF;
int mx = -INF;

/* 
void calculate()
{
	int sum = number[0];
	for (int i = 1; i < n; i++)
	{
		int num = number[i];
		switch (cal[i - 1])
		{
		case 0:
			sum += num;
			break;
		case 1:
			sum -= num;
			break;
		case 2:
			sum *= num;
			break;
		case 3:
			if (sum < 0)
			{
				sum *= -1;
				sum /= num;
				sum *= -1;
			}
			else
				sum /= num;
			break;
		}
	}
	mn = min(mn, sum);
	mx = max(mx, sum);
}
void divDfs(int idx, int cnt)
{
	if (oper[3] == cnt)
	{
		calculate();
		return;
	}
	for (int i = idx; i < n - 1; i++)
	{
		if (visited[i])
			continue;

		visited[i] = true;
		cal[i] = 3;

		divDfs(idx + 1, cnt + 1);

		visited[i] = false;
		cal[i] = -1;
	}
}
void mulDfs(int idx, int cnt)
{
	if (oper[2] == cnt)
	{
		divDfs(0, 0);
		return; 
	}
	for (int i = idx; i < n - 1; i++)
	{
		if (visited[i])
			continue;

		visited[i] = true;
		cal[i] = 2;

		mulDfs(idx + 1, cnt + 1);

		visited[i] = false;
		cal[i] = -1;
	}
}
void minusDfs(int idx, int cnt)
{
	if (oper[1] == cnt)
	{
		mulDfs(0, 0);
		return;
	}
	for (int i = idx; i < n - 1; i++)
	{
		if (visited[i])
			continue;

		visited[i] = true;
		cal[i] = 1;

		minusDfs(idx + 1, cnt + 1);

		visited[i] = false;
		cal[i] = -1;
	}
}
void plusDfs(int idx, int cnt)
{
	if (oper[0] == cnt)
	{
		minusDfs(0, 0);
		return;
	}
	for (int i = idx; i < n - 1; i++)
	{
		if (visited[i] && cal[i] != -1)
			continue;

		visited[i] = true;
		cal[i] = 0;

		plusDfs(idx + 1, cnt + 1);

		visited[i] = false;
		cal[i] = -1;
	}
}
void solution()
{
	memset(cal, -1, sizeof(cal));
	plusDfs(0, 0);

	cout << mx << "\n" << mn << '\n';
}
*/

void solve(int idx, int value)
{
	if (idx == n - 1)
	{
		mn = min(mn, value);
		mx = max(mx, value);
		return;
	}
	if (oper[0])
	{
		oper[0]--;
		solve(idx + 1, value + number[idx + 1]);
		oper[0]++;
	}
	if (oper[1])
	{
		oper[1]--;
		solve(idx + 1, value - number[idx + 1]);
		oper[1]++;
	}
	if (oper[2])
	{
		oper[2]--;
		solve(idx + 1, value * number[idx + 1]);
		oper[2]++;
	}
	if (oper[3])
	{
		oper[3]--;
		solve(idx + 1, value / number[idx + 1]);
		oper[3]++;
	}
}
void input()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> number[i];
	}
	for (int i = 0; i < 4; i++)
	{
		cin >> oper[i];
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve(0, number[0]);

	cout << mx << '\n';
	cout << mn << '\n';

	return 0;
}
