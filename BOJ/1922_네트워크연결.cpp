#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_COMPUTER = 1000 + 1;
const int MAX_LINE = 100000;

struct LOCATION
{
	int c1, c2;
};

struct COMPUTER
{
	int c1, c2;	// 각각 연결된 컴퓨터 
	int cost;	// 연결 비용
	bool visit;	// 방문체크
};

int n, m;		// 컴퓨터개수, 연결된 선의 개수	
ll result;		// 총 연결 비용

COMPUTER computer[MAX_LINE];	// 컴퓨터 정보

int cost[MAX_LINE];			// 연결비용을 오름차순으로 정렬
int parent[MAX_LINE];		// 부모노드 저장 배열

// origin이 부모노드인 모든 컴퓨터를 change를 부모로 바꾼다.
void changeParent(int origin, int change)
{
	for (int i = 1; i <= m; i++)
	{
		if (parent[i] == origin)
			parent[i] = change;
	}
}

// 부모노드 찾기
int findParent(int a)
{
	if (parent[a] == a)
		return a;
	return findParent(parent[a]);
}

// 부모노드 합치기
void unionParent(int a, int b)
{
	a = findParent(a);
	b = findParent(b);

	// 둘 중 부모노드가 작은 걸로 부모노드 설정
	if (a < b)
	{
		parent[b] = a;
		changeParent(b, a);
	}
	else
	{
		parent[a] = b;
		changeParent(a, b);
	}
}

// 부모노드가 같은지 확인
bool checkParent(int a, int b)
{
	a = findParent(a);
	b = findParent(b);

	if (a == b)
		return true;
	else
		return false;
}

// 두 개의 컴퓨터가 연결되었는지 확인
bool checkConnection()
{
	for (int i = 1; i < n; i++)
	{
		if (parent[i] != parent[i + 1])
			return false;
	}
	return true;
}

// 해당 코스트의 컴퓨터의 번호를 반환
LOCATION findComputer(int ncost)
{
	for (int i = 0; i < m; i++)
	{
		// 연결이 된 컴퓨터는 보지않는다.
		if (computer[i].visit)
			continue;

		if (computer[i].cost == ncost)
		{
			computer[i].visit = true;
			return { computer[i].c1, computer[i].c2 };
		}
	}
	return { -1, -1 };
}


void solve()
{
	result = 0;

	// 부모노드 초기화
	for (int i = 1; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++)
	{
		// 두 개의 컴퓨터가 연결되었는지 확인
		if (checkConnection())
			break;

		int ncost = cost[i];
		LOCATION lo = findComputer(ncost);
		
		// -1면 이미 연결되었는 컴퓨터이다.
		if (lo.c1 == -1 || lo.c2 == -1)
			continue;

		// 부모노드가 같은지 확인
		if (checkParent(lo.c1, lo.c2))
			continue;

		// 컴퓨터를 연결시킨다.
		unionParent(lo.c1, lo.c2);

		// 연결된 컴퓨터의 코스트를 더해준다.
		result += ncost;
	}
}

// 입력
void input()
{
	int idx = 0;

	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		computer[idx] = { a, b, c, false };
		cost[idx++] = c;
	}

	sort(cost, cost + idx);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	cout << result << '\n';
	return 0;
}
