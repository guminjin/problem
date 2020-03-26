#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 10 + 1;		// �������� �ִ� ũ��
const int MAX_LAND = 6 + 1;	// ���� �ִ� ��

struct XY
{
	int y, x;
};

int garo, sero;			// ����, ������ ����

int MAP[MAX][MAX];		// ���� �ٴٸ� ����
int visited[MAX][MAX];	// ���� ��ȣ�� �ű涧 �湮Ȯ��

int landCnt;			// ���� ����
XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } }; // �����¿� ����

int bridge[MAX_LAND][MAX_LAND];			// ���� ���� ����� �ٸ��� ����
int visitBridge[MAX_LAND][MAX_LAND];	// �̹� ����� ������ Ȯ��

int allLen[MAX_LAND*MAX_LAND];			// ��� ���� �����ϴ� �ٸ��� ���� ����
int allLenCnt;							// �� �ٸ��� ����

int parent[MAX_LAND];	// �� ���� �θ��带 ����

int result;				// �ּ� �ٸ��� ���� ����

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

// p�� �θ� �Ǿ��ִ� ��� ���� �θ� change�� �ٲ�
void changeParent(int p, int change)
{
	for (int i = 1; i <= landCnt; i++)
	{
		if (parent[i] == p)
			parent[i] = change;
	}
}

// �ش� ���� �θ� ã��
int findParent(int p)
{
	if (parent[p] == p)
		return p;

	return findParent(parent[p]);
}

// ���� �θ� ���� �����.
void unionParent(int a, int b)
{
	// a, b ���� �θ� ã�´�.
	a = findParent(a);	
	b = findParent(b);

	// ���� ���� �θ� ����
	if (a < b)
	{
		parent[b] = a;
		
		// b�� �θ� �Ǿ��ִ� ��� ���� �θ� a�� �ٲ�
		changeParent(b, a);
	}
	else
	{
		parent[a] = b;

		// a�� �θ� �Ǿ��ִ� ��� ���� �θ� b�� �ٲ�
		changeParent(a, b);
	}
}

// ������ ���� �θ� Ȯ��
bool cmpParent(int a, int b)
{
	a = findParent(a);
	b = findParent(b);

	if (a == b)
		return true;
	else
		return false;
}

// num ũ��� ����Ǿ��ִ� ���� ã�´�.
XY findLocation(int num)
{
	for (int y = 1; y <= landCnt; y++)
	{
		for (int x = 1; x <= landCnt; x++)
		{
			// �ش� ���� �����ߴ��� Ȯ��
			if (visitBridge[y][x])
				continue;

			// ���� ���� ���� ã������
			if (num == bridge[y][x])
			{
				// �ش� �� �ΰ��� �湮�ߴٰ� ǥ�� �� �ΰ��� ���� ��ȣ ��ȯ
				visitBridge[y][x] = visitBridge[x][y] = true;
				return { y, x };
			}
		}
	}
	return { -1, -1 };
}

// ��� ���� �θ� �ϳ��� �Ǿ����� Ȯ��
bool checkConnect()
{
	for (int i = 1; i < landCnt; i++)
	{
		// �θ� �ٸ��� �ִٸ� ��� ������� ����
		if (parent[i] != parent[i + 1])
			return false;
	}

	return true;
}

// �ּ� ���� Ʈ���� �̿��ϱ� ���� �迭 ����
void initParent()
{
	// ����Ǿ��ִ� ������ �ٸ��� ���̸� allLen�� �ִ´�
	for (int y = 1; y <= landCnt; y++)
	{
		for (int x = 1; x <= landCnt; x++)
		{
			if (!bridge[y][x])
				continue;

			allLen[allLenCnt++] = bridge[y][x];
		}
	}

	// allLen�� ������������ ����
	sort(allLen, allLen + allLenCnt);

	// �� ���� �θ� �ڱ��ڽ����� �ʱ�ȭ
	for (int i = 1; i <= landCnt; i++)
		parent[i] = i;
}

// �ּ� ���� Ʈ���� �̿���
// ��� ���� ����Ǵ� �ּ��� �ٸ��� ã�´�.
void mst()
{
	// �ּ� ���� Ʈ���� �̿��ϱ� ���� �迭 ����
	initParent();

	result = 0;

	// �ٸ��� ���̰� ����Ǿ��ִ� ������ 0���� ������ Ȯ���ϸ�
	// ������ ������ �����Ų��.
	for (int i = 0; i < allLenCnt; i++)
	{
		// ��� ���� �θ� �ϳ��� �Ǿ����� Ȯ��
		if (checkConnect())
			break;

		// allLen[i]�� ũ��� ����Ǿ��ִ� ���� ã�´�.
		XY now = findLocation(allLen[i]);
		
		// -1�̸� �ش� ũ���� �ٸ��� ����Ǿ��ִ� ������ üũ�Ǿ
		// ���� �ٸ��� ũ�⸦ ����.
		if (now.x == -1 || now.y == -1)
			continue;

		// �ΰ��� ���� �θ� ������ �������� ����
		if (cmpParent(now.y, now.x))
			continue;
		
		// �ΰ��� ���� �θ� �ٸ��ٸ�
		// �ٸ��� �������ְ�, �θ� ���� �����
		result += bridge[now.y][now.x];
		unionParent(now.y, now.x);
	}
	if (!checkConnect())
		result = -1;
}

// �ٸ� ���� ����Ǵ��� Ȯ��
void checkBridge(XY start)
{
	for (int i = 0; i < 4; i++)
	{
		XY next = start;
		
		// ���� ���� ����� �� �ٸ��� ���� ����
		int len = 0;

		// �ٸ� ���� ����Ǵ��� Ȯ���ϴ� ����
		int connect = 0;
		while (1)
		{
			next.x += dir[i].x;
			next.y += dir[i].y;

			// �������� ���� Ȯ��
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				break;

			// �ٸ� ���� �����ٸ�
			if (MAP[next.y][next.x])
			{
				// connect�� ���� ���ڸ� ����
				connect = MAP[next.y][next.x];
				break;
			}

			// �ٸ��� ���� ����
			len++;
		}
		
		// �ٸ��� ���̴� 2�̻��̾�� �Ѵ�
		if (len < 2)
			continue;

		// �ٸ� ���� �������� Ȯ��
		// connect�� 0�̶�� �ƹ� ������ ����������
		if (connect)
		{
			// ������ ���� ��ȣ�� �����ϴ� ����
			int s = MAP[start.y][start.x];

			// �� ���� �̹� ����Ǿ��ִٸ� �ٸ��� �ּڰ��� ����
			if (bridge[s][connect])
				len = min(len, bridge[s][connect]);

			bridge[s][connect] = len;
			bridge[connect][s] = len;
		}
	}
}

// ������ ������ �� �ִ� �ּ� ������ �ٸ� ã��
void findBridge()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			// �ٴ� Ȯ��
			if (!MAP[y][x])
				continue;

			// ���� ��ġ���� ������ �� �ִ� �ٸ� ���� Ȯ��
			checkBridge({ y,x });
		}
	}
}

// ���� ��ȣ ���̱�
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

		// �����¿쿡 ������ �� ã��
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;

			// ������ ���� Ȯ��
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			// �ٴ����� Ȯ��
			if (!MAP[next.y][next.x])
				continue;
			// �̹� �湮�� �� Ȯ��
			if (visited[next.y][next.x])
				continue;

			// �����ǿ� ���� ��ȣ�� �ְ�, �ش� ��ġ�� �湮ǥ��
			MAP[next.y][next.x] = landCnt;
			visited[next.y][next.x] = true;

			// �ش���ġ q�� �־� ������ ���� �ִ��� Ȯ��
			q.push(next);
		}
	}
}

// ������ ���� ã�� ��ȣ�� ���δ�.
void findLand()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			// �湮�� ���� �ٽ� �湮���� �ʴ´�.
			if (visited[y][x])
				continue;

			// 0�̶�� �ٴ�
			if (!MAP[y][x])
				continue;

			// 1�� ���̹Ƿ� ���� ã�´�
			// landCnt�� �ش� ��ġ�� ���� ��ȣ�� ���δ�. 
			bfsLand({ y,x }, ++landCnt);
		}
	}
}


void solve()
{
	// ������ ���� ã�� ��ȣ�� ���δ�.
	findLand();

	// ������ ������ �� �ִ� �ּ� ������ �ٸ� ã��
	findBridge();

	// ��� ������ ����� �� �ִ� �ּ� �ٸ����� ���ϱ�
	mst();
	cout << result << '\n';
}

// �Է�
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