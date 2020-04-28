#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_POINT = 10000 + 1;
const int MAX_LINE = 100000 + 1;

struct POINT
{
	int cost;
	int p1, p2;

	// 오름차순 정렬
	bool operator< (POINT com)
	{
		if (cost < com.cost)
			return true;
		return false;
	}
};

int v, e;
POINT dust[MAX_LINE];	// 연결된 두개의 정점과, 비용을 저장하는 배열
int parent[MAX_POINT];	// 부모노드 저장 배열
ll result;				// 최소 비용 변수

// 부모노르를 찾는다.
int findParent(int p)
{
	if (parent[p] == p)
		return p;
	return findParent(parent[p]);
}

// 부모노드를 같게 만든다.
void unionParent(int p1, int p2)
{
	p1 = findParent(p1);
	p2 = findParent(p2);

	if (p1 < p2)
		parent[p2] = p1;
	else
		parent[p1] = p2;
}

// 두개의 정점의 부모노드가 같은지 확인
bool checkParent(int p1, int p2)
{
	p1 = findParent(p1);
	p2 = findParent(p2);

	if (p1 == p2)
		return true;
	else
		return false;
}

void solve()
{
	result = 0;

	// 부모노드 초기화
	for (int i = 1; i <= v; i++)
		parent[i] = i;

	// 모든 선을 확인한다.
	for (int i = 0; i < e; i++)
	{
		// 부모노드를 확인
		if (!checkParent(dust[i].p1, dust[i].p2))
		{
			// 부모노드를 같게 해주고, 선을 연결
			unionParent(dust[i].p1, dust[i].p2);
			result += dust[i].cost;
		}
	}
}
void input()
{
	cin >> v >> e;
	for (int i = 0; i < e; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		dust[i] = { c, a, b };
	}
	sort(dust, dust + e);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	cout << result << '\n';
	return 0;
}
