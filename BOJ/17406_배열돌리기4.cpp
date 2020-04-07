#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 50 + 1;
const int INF = 987654321;

struct TURN
{
	int startY, startX;
	int endY, endX;
	bool visit;
};

int garo, sero, k;
int mem[MAX][MAX];
TURN turn[6];		// ���� ����
int result = INF;

// ������ -> �Ʒ� -> ���� -> ��
int X[4] = { 1, 0, -1, 0 };
int Y[4] = { 0, 1, 0, -1 };

void print()
{
	cout << endl;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			cout << mem[y][x] << ' ';
		}
		cout << endl;
	}
}

// �迭�� �ּڰ��� ã�´�.
void findMin()
{
	for (int y = 1; y <= sero; y++)
	{
		int sum = 0;
		for (int x = 1; x <= garo; x++)
		{
			sum += mem[y][x];
		}
		result = min(result, sum);
	}
}

// ������ ����
void turnArr(TURN now)
{
	int startY = now.startY;
	int startX = now.startX;
	int endY = now.endY;
	int endX = now.endX;

	while (1)
	{
		// �ð�������� ���鼭 �迭�� ���� ����
		vector<int> v;

		// ���������� ���� ���µ�
		// ���ۺ��� X[i]�� ���� ���ϰ� �����ϱ⶧����
		// nx�� ���� 1 ���ش�.
		int ny = startY;
		int nx = startX - 1;
		int len = endX - startX + 1;
		int l = len;

		// �ð�������� ���鼭 ���� ����
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < l; j++)
			{
				ny += Y[i];
				nx += X[i];

				v.push_back(mem[ny][nx]);
			}
			
			// ũ�Ⱑ 4�϶� �Ʒ�ó�� i�������� �̵��Ѵ�.
			// ���� i�� 0 �Ǵ� 2�� �� len�� -1���ش�.
			//	0 0 0 0
			//	3 . . 1
			//	3 . . 1
			//	2 2 2 1
			if (i == 0 || i == 2)
				l--;
		}

		// v�� ����� �̿��� rotate �����ش�.
		int size = v.size();
		rotate(v.begin(), v.begin() + size - 1, v.end());


		// �ٽ� ���� �ִ� �ڸ��� ��ĭ�� �̵��� ����� �־��ش�.
		ny = startY;
		nx = startX - 1;
		l = len;
		int idx = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < l; j++)
			{
				ny += Y[i];
				nx += X[i];

				mem[ny][nx] = v[idx++];
			}
			if (i == 0 || i == 2)
				l--;
		}

		startX++, startY++;
		endX--, endY--;
		
		// ���� ��ġ�� �� �̻� ȸ����ų �� ����.
		if (startX == endX && startY == endY)
			break;
	}
}

// �迭 ����
void copyArr(int origin[][MAX], int copy[][MAX])
{
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			copy[y][x] = origin[y][x];
		}
	}
}

// ȸ���� ������ ���Ƿ� ����
void dfs(int cnt)
{
	// ��� ȸ���� �����ߴٸ�
	if (cnt == k)
	{
		// �迭�� �ּڰ��� ã�´�.
		findMin();
		return;
	}
	for (int i = 0; i < k; i++)
	{
		// �̹� ������ ���� üũ
		if (turn[i].visit)
			continue;
		
		// ���� �迭�� temp�� �����صд�.
		int temp[MAX][MAX];
		copyArr(mem, temp);

		// ������ ����
		turnArr(turn[i]);
		// �ش� ������ �����ߴٰ� üũ
		turn[i].visit = true;

		// cnt�� 1�����ϰ� ���� ������ ã�´�.
		dfs(cnt + 1);
		
		// �ش� ������ �������� �ʾҴٰ� üũ
		turn[i].visit = false;
		// �ش� ������ �����ϱ� ���� ���·� �ǵ�����.
		copyArr(temp, mem);
	}
}


void solve()
{
	// ȸ���� ������ ���Ƿ� ����
	dfs(0);

	// �迭�� �ּڰ� ���
	cout << result << '\n';
}

// �Է�
void input()
{
	cin >> sero >> garo >> k;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			cin >> mem[y][x];
		}
	}
	for (int i = 0; i < k; i++)
	{
		int r, c, s;
		cin >> r >> c >> s;
		turn[i] = { (r - s), (c - s), (r + s), (c + s), false };
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();

	return 0;
}
