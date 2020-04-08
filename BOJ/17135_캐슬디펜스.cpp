#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 15 + 1;

// queue
struct INFO
{
	int y, x;
	int dis;
};

int garo, sero, dis;
int map[MAX][MAX];		
int visited[MAX][MAX];
int origin[MAX][MAX];	// �ʱ� map
bool archer[MAX];		// �ü��� ��ġ
int result;

int X[3] = { -1, 0, 1 };
int Y[3] = { 0, -1, 0 };

bool checkTarget()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (map[y][x])
				return false;
		}
	}
	return true;
}
void moveTarget()
{
	for (int y = sero - 1; y >= 0; y--)
	{
		for (int x = 0; x < garo; x++)
		{
			if (!map[y][x])
				continue;
			else
			{
				if (y + 1 == sero)
				{
					map[y][x] = 0;
					continue;
				}

				map[y][x] = 0;
				map[y + 1][x] = 1;
			}
		}
	}
}

// �ѹ��� ���ݿ� ���� �� �ִ� ���� �� ���ϱ�
int findTarget()
{
	int targetX[3];	// �� ������ �ü��� ���� �� �ִ� ���� ��ġ�� ����
	int targetY[3];
	for (int i = 0; i < 3; i++)
		targetX[i] = targetY[i] = -1;
	
	int targetIdx = 0;

	// archer[i]�� true��� i��° ��ġ�� �ü��� �ִ�.
	for (int i = 0; i < garo; i++)
	{
		// �ش� ��ġ�� �ü��� �ִ��� Ȯ��
		if (!archer[i])
			continue;

		memset(visited, 0, sizeof(visited));
		queue<INFO> q;
		q.push({ sero, i, 0 });
		
		bool flg = false;	// �ü��� ���� ��Ҵ��� Ȯ��
		int distance = 0;	// �Ÿ��� dis������ �� ���� Ž��

		// ���� ������ �ݺ��� ����
		while (!flg)
		{
			INFO now = q.front(); q.pop();	
			INFO next;						
			
			// ���� �Ÿ� ���Ѻ��� ũ�� ����
			if (now.dis == dis)
				break;

			// ����, ��, ������ ���� ������ ���� �ִ��� Ȯ��
			for (int j = 0; j < 3; j++)
			{
				next.y = now.y + Y[j];
				next.x = now.x + X[j];
				next.dis = now.dis + 1;

				// ����üũ
				if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
					continue;
				//�̹� �湮�� ��ġ���� üũ
				if (visited[next.y][next.x])
					continue;

				// �ش� ��ġ�� ���� �ִٸ�, 
				// target�� ��ġ�� ���� �� ���� ��Ҵٰ� flg�� true�� ����
				// while�� ����
				if (map[next.y][next.x])
				{
					flg = true;
					targetX[targetIdx] = next.x;
					targetY[targetIdx] = next.y;
					break;
				}

				// �ش� ��ġ�� ���� ���ٸ�,
				// q�� push
				visited[next.y][next.x] = true;
				q.push(next);
			}
		}
		// ���� �ü�
		targetIdx++;
	}

	int findCnt = 0;
	for (int i = 0; i < 3; i++) 
	{
		if (targetX[i] == -1 || targetY[i] == -1)
			continue;
		if (!map[targetY[i]][targetX[i]])
			continue;

		map[targetY[i]][targetX[i]] = 0;
		findCnt++;
	}

	return findCnt;
}

// �ü��� ��ġ�� ���Ѵ�.
void selectArcherLocation(int idx, int cnt)
{
	// ������ �ü��� ��ġ�� �������ٸ�
	if (cnt == 3) 
	{
		// ó�� ���¸� ���������ش�.
		for (int y = 0; y < sero; y++)
		{
			for (int x = 0; x < garo; x++)
			{
				map[y][x] = origin[y][x];
			}
		}

		// ���� ���� ��
		int sum = 0;
		// map�� ������ ��� ����� ������ �ݺ�
		while (!checkTarget())
		{
			// �ѹ��� ���ݿ� ���� �� �ִ� ���� �� ���ϱ�
			sum += findTarget();
			moveTarget();
		}

		// ���� ���� ����� ��� ����
		result = max(result, sum);

		return;
	}

	for (int i = 0; i < garo; i++)
	{
		// �̹� ���õ� �ü��� ��ġ���� üũ
		if (archer[i])
			continue;

		// ���õǾ��ٰ� ǥ��
		archer[i] = true;
		
		// ���� �ü��� ��ġ�� ã�´�.
		selectArcherLocation(i + 1, cnt + 1);

		// �������
		archer[i] = false;

	}
}

// �Է�
void input()
{
	cin >> sero >> garo >> dis;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> map[y][x];
			origin[y][x] = map[y][x];
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	selectArcherLocation(0, 0);
	cout << result << '\n';
	return 0;
}
