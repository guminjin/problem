#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_COMPUTER = 1000 + 1;
const int MAX_LINE = 100000;

struct COMPUTER
{
	int c1, c2;	// 각각 연결된 컴퓨터 
	int cost;	// 연결 비용
	bool visit;	// 방문체크

	// 오름차순 정렬
	bool operator<(COMPUTER com)
	{
		if (cost < com.cost)
			return true;
		return false;
	}
};

int n, m;		// 컴퓨터개수, 연결된 선의 개수	
ll result;		// 총 연결 비용

COMPUTER computer[MAX_LINE];	// 컴퓨터 정보
int parent[MAX_LINE];			// 부모노드 저장 배열

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
		parent[b] = a;
	else
		parent[a] = b;
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

void solve()
{
	result = 0;

	// 부모노드 초기화
	for (int i = 1; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++)
	{
		// 부모노드가 같은지 확인
		if (!checkParent(computer[i].c1, computer[i].c2))
		{
			// 컴퓨터를 연결시킨다.
			unionParent(computer[i].c1, computer[i].c2);

			// 연결된 컴퓨터의 코스트를 더해준다.
			result += computer[i].cost;
		}
	}
}

// 입력
void input()
{
	int idx = 0;

	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		computer[i] = { a, b, c, false };
	}
	sort(computer, computer + m);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	cout << result << '\n';
	return 0;
}
