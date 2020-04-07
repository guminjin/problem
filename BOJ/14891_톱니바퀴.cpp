#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <deque>
#include <string>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAX_TURN = 100;

struct INFO
{
	int num;
	int dir;
};

int inning;
deque<int> deq[5];		// wheel status
bool visited[5];		// wheel visited check 
int turn[5];			// wheel turn check
int X[2] = { -1, 1 };

void print()
{
	cout << endl;
	cout << "0 1 2 3 4 5 6 7" << endl;
	cout << "---------------" << endl;
	for (int i = 1; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << deq[i][j] << ' ';
		cout << endl;
	}
}
// calculate grade
int calGrade()
{
	int sum = 0;
	int mul = 1;
	for (int i = 1; i < 5; i++)
	{
		sum += (deq[i][0] * mul);
		mul *= 2;
	}
	return sum;
}
// compare pole
bool checkDir(int now, int next, int dir)
{
	// == don't turn
	if (dir == 0)
	{
		if (deq[now][6] == deq[next][2])
			return true;
	}
	else if (dir == 1)
	{
		if (deq[now][2] == deq[next][6])
			return true;
	}

	// != turn
	return false;
}
void turnWheel(int num, int dir)
{
	if (dir == 1)
	{
		int front = deq[num].back();
		deq[num].pop_back();
		deq[num].push_front(front);
	}
	else if (dir == -1)
	{
		int back = deq[num].front();
		deq[num].pop_front();
		deq[num].push_back(back);
	}
	else
		return;
}
void solution(INFO now)
{
	memset(visited, 0, sizeof(visited));
	memset(turn, 0, sizeof(turn));

	queue<INFO> q;
	q.push(now);
	visited[now.num] = true;
	turn[now.num] = now.dir;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;
		next.dir = now.dir * -1;
		for (int i = 0; i < 2; i++)
		{
			next.num = now.num + X[i];
			if (next.num < 1 || next.num > 4)
				continue;
			if (visited[next.num])
				continue;

			visited[next.num] = true;

			// pole same
			if (checkDir(now.num, next.num, i))
			{
				// don't turn
				turn[next.num] = 0;
				continue;
			}
			// pole different
			else
				turn[next.num] = next.dir;	// opposite direction turn

			q.push(next);
		}
	}

	for (int i = 1; i < 5; i++)
		turnWheel(i, turn[i]);
}
void input()
{
	for (int i = 1; i < 5; i++)
	{
		string s; cin >> s;
		for (int j = 0; j < s.length(); j++)
			deq[i].push_back((s[j] - '0'));
	}
	cin >> inning;
	for (int i = 0; i < inning; i++)
	{
		int num, dir;
		cin >> num >> dir;
		solution({ num, dir });
	}
	cout << calGrade() << '\n';
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();

	return 0;
}