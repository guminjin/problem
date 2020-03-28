#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_POINT = 10000;
const int MAX_LINE = 100000;

struct P
{
	int p1, p2;
};

struct POINT
{
	int p1, p2;
	int cost;
	bool visit;
};

int v, e;
POINT point[MAX_LINE];
int cost[MAX_LINE];
int parent[MAX_POINT];
ll result;

int findParent(int p)
{
	if (parent[p] == p)
		return p;
	return findParent(parent[p]);
}
void changeParent(int origin, int change)
{
	for (int i = 1; i <= v; i++)
	{
		if (parent[i] == origin)
			parent[i] = change;
	}
}
void unionParent(int p1, int p2)
{
	p1 = findParent(p1);
	p2 = findParent(p2);

	if (p1 < p2)
	{
		parent[p2] = p1;
		changeParent(p2, p1);
	}
	else
	{
		parent[p1] = p2;
		changeParent(p1, p2);
	}
}
bool checkParent(int p1, int p2)
{
	p1 = findParent(p1);
	p2 = findParent(p2);

	if (p1 == p2)
		return true;
	else
		return false;
}
bool checkConnect()
{
	for (int i = 1; i < v; i++)
	{
		if (parent[i] != parent[i + 1])
			return false;
	}
	return true;
}
P findPoint(int cost)
{
	for (int i = 0; i < e; i++)
	{
		if (point[i].visit)
			continue;
		
		if (point[i].cost == cost)
			return { point[i].p1, point[i].p2 };
	}
	return { -1, -1 };
}
void solve()
{
	result = 0;

	for (int i = 1; i <= v; i++)
		parent[i] = i;

	for (int i = 0; i < e; i++)
	{
		if (checkConnect())
			break;

		P p = findPoint(cost[i]);
		if (p.p1 == -1 || p.p2 == -1)
			continue;

		if (checkParent(p.p1, p.p2))
			continue;

		unionParent(p.p1, p.p2);
		result += cost[i];
	}
}
void input()
{
	cin >> v >> e;
	for (int i = 0; i < e; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		point[i] = { a, b, c, false };
		cost[i] = c;
	}
	sort(cost, cost + e);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	cout << result << '\n';
	return 0;
}
