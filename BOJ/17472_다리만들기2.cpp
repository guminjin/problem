#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 10 + 1;		// 격자판의 최대 크기
const int MAX_LAND = 6 + 1;	// 섬의 최대 수

struct XY
{
	int y, x;
};

int garo, sero;			// 가로, 세로의 길이

int MAP[MAX][MAX];		// 땅과 바다를 저장
int visited[MAX][MAX];	// 섬에 번호를 매길때 방문확인

int landCnt;			// 섬의 개수
XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } }; // 상하좌우 방향

int bridge[MAX_LAND][MAX_LAND];			// 섬과 섬이 연결된 다리의 길이
int visitBridge[MAX_LAND][MAX_LAND];	// 이미 연결된 섬인지 확인

int allLen[MAX_LAND*MAX_LAND];			// 모든 섬을 연결하는 다리의 길이 저장
int allLenCnt;							// 총 다리의 개수

int parent[MAX_LAND];	// 각 섬의 부모노드를 저장

int result;				// 최소 다리의 길이 저장

void print()
{
	cout << '\n';
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cout << MAP[y][x] <<' ';
		}
		cout << '\n';
	}
}

// p로 부모가 되어있는 모든 섬의 부모를 change로 바꿈
void changeParent(int p, int change)
{
	for (int i = 1; i <= landCnt; i++)
	{
		if (parent[i] == p)
			parent[i] = change;
	}
}

// 해당 섬의 부모를 찾음
int findParent(int p)
{
	if (parent[p] == p)
		return p;

	return findParent(parent[p]);
}

// 섬의 부모를 같게 만든다.
void unionParent(int a, int b)
{
	// a, b 섬의 부모를 찾는다.
	a = findParent(a);	
	b = findParent(b);

	// 작은 수로 부모를 설정
	if (a < b)
	{
		parent[b] = a;
		
		// b로 부모가 되어있는 모든 섬의 부모를 a로 바꿈
		changeParent(b, a);
	}
	else
	{
		parent[a] = b;

		// a로 부모가 되어있는 모든 섬의 부모를 b로 바꿈
		changeParent(a, b);
	}
}

// 각각의 섬의 부모를 확인
bool cmpParent(int a, int b)
{
	a = findParent(a);
	b = findParent(b);

	if (a == b)
		return true;
	else
		return false;
}

// num 크기로 연결되어있는 섬을 찾는다.
XY findLocation(int num)
{
	for (int y = 1; y <= landCnt; y++)
	{
		for (int x = 1; x <= landCnt; x++)
		{
			// 해당 섬을 연결했는지 확인
			if (visitBridge[y][x])
				continue;

			// 연결 안한 섬을 찾았으면
			if (num == bridge[y][x])
			{
				// 해당 섬 두개를 방문했다고 표시 후 두개의 섬의 번호 반환
				visitBridge[y][x] = visitBridge[x][y] = true;
				return { y, x };
			}
		}
	}
	return { -1, -1 };
}

// 모든 섬의 부모가 하나가 되었는지 확인
bool checkConnect()
{
	for (int i = 1; i < landCnt; i++)
	{
		// 부모가 다른게 있다면 모두 연결되지 않음
		if (parent[i] != parent[i + 1])
			return false;
	}

	return true;
}

// 최소 신장 트리를 이용하기 위한 배열 설정
void initParent()
{
	// 연결되어있는 섬들의 다리의 길이를 allLen에 넣는다
	for (int y = 1; y <= landCnt; y++)
	{
		for (int x = 1; x <= landCnt; x++)
		{
			if (!bridge[y][x])
				continue;

			allLen[allLenCnt++] = bridge[y][x];
		}
	}

	// allLen을 오름차순으로 정렬
	sort(allLen, allLen + allLenCnt);

	// 각 섬의 부모를 자기자신으로 초기화
	for (int i = 1; i <= landCnt; i++)
		parent[i] = i;
}

// 최소 신장 트리를 이용해
// 모든 섬이 연결되는 최소의 다리를 찾는다.
void mst()
{
	// 최소 신장 트리를 이용하기 위한 배열 설정
	initParent();

	result = 0;

	// 다리의 길이가 저장되어있는 변수를 0부터 끝까지 확인하며
	// 각각의 섬들을 연결시킨다.
	for (int i = 0; i < allLenCnt; i++)
	{
		// 모든 섬의 부모가 하나가 되었는지 확인
		if (checkConnect())
			break;

		// allLen[i]의 크기로 연결되어있는 섬을 찾는다.
		XY now = findLocation(allLen[i]);
		
		// -1이면 해당 크기의 다리로 연결되어있는 섬들은 체크되어서
		// 다음 다리의 크기를 본다.
		if (now.x == -1 || now.y == -1)
			continue;

		// 두개의 섬의 부모가 같으면 다음으로 진행
		if (cmpParent(now.y, now.x))
			continue;
		
		// 두개의 섬의 부모가 다르다면
		// 다리를 연결해주고, 부모를 같게 만든다
		result += bridge[now.y][now.x];
		unionParent(now.y, now.x);
	}
	if (!checkConnect())
		result = -1;
}

// 다른 섬과 연결되는지 확인
void checkBridge(XY start)
{
	for (int i = 0; i < 4; i++)
	{
		XY next = start;
		
		// 섬과 섬이 연결될 때 다리의 길이 변수
		int len = 0;

		// 다른 섬과 연결되는지 확인하는 변수
		int connect = 0;
		while (1)
		{
			next.x += dir[i].x;
			next.y += dir[i].y;

			// 격자판의 범위 확인
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				break;

			// 다른 땅을 만났다면
			if (MAP[next.y][next.x])
			{
				// connect에 섬의 숫자를 저장
				connect = MAP[next.y][next.x];
				break;
			}

			// 다리의 길이 증가
			len++;
		}
		
		// 다리의 길이는 2이상이어야 한다
		if (len < 2)
			continue;

		// 다른 섬과 만났는지 확인
		// connect가 0이라면 아무 땅과도 만나지않음
		if (connect)
		{
			// 시작한 섬의 번호를 저장하는 변수
			int s = MAP[start.y][start.x];

			// 두 섬이 이미 연결되어있다면 다리의 최솟값을 저장
			if (bridge[s][connect])
				len = min(len, bridge[s][connect]);

			bridge[s][connect] = len;
			bridge[connect][s] = len;
		}
	}
}

// 섬간에 연결할 수 있는 최소 길이의 다리 찾기
void findBridge()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			// 바다 확인
			if (!MAP[y][x])
				continue;

			// 땅의 위치마다 연결할 수 있는 다른 섬을 확인
			checkBridge({ y,x });
		}
	}
}

// 섬에 번호 붙이기
void bfsLand(XY start, int landCnt)
{
	queue<XY> q;
	q.push(start);
	visited[start.y][start.x] = true;
	MAP[start.y][start.x] = landCnt;

	while (!q.empty())
	{
		XY now = q.front(); q.pop();
		XY next;

		// 상하좌우에 인접한 땅 찾기
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;

			// 격자판 범위 확인
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			// 바다인지 확인
			if (!MAP[next.y][next.x])
				continue;
			// 이미 방문한 땅 확인
			if (visited[next.y][next.x])
				continue;

			// 격자판에 섬의 번호를 넣고, 해당 위치에 방문표시
			MAP[next.y][next.x] = landCnt;
			visited[next.y][next.x] = true;

			// 해당위치 q에 넣어 주위에 땅이 있는지 확인
			q.push(next);
		}
	}
}

// 각각의 섬을 찾아 번호를 붙인다.
void findLand()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			// 방문한 곳은 다시 방문하지 않는다.
			if (visited[y][x])
				continue;

			// 0이라면 바다
			if (!MAP[y][x])
				continue;

			// 1은 땅이므로 섬을 찾는다
			// landCnt는 해당 위치에 섬의 번호를 붙인다. 
			bfsLand({ y,x }, ++landCnt);
		}
	}
}


void solve()
{
	// 각각의 섬을 찾아 번호를 붙인다.
	findLand();

	// 섬간에 연결할 수 있는 최소 길이의 다리 찾기
	findBridge();

	// 모든 섬들이 연결될 수 있는 최소 다리길이 구하기
	mst();
	cout << result << '\n';
}

// 입력
void input()
{
	cin >> sero >> garo;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> MAP[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	return 0;
}