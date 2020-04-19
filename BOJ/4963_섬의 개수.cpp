#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 51;

struct XY
{
	int y, x;
};

int garo, sero;
int map[MAX][MAX];
int visited[MAX][MAX];

//�����¿�, �밢�� ��� Ȯ��
XY dir[] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
			 {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

// �ش� ��ġ�� ���� ����� ��� ���� ã�´�.
void bfs(XY start)
{
	queue<XY> q;
	q.push(start);

	while (!q.empty())
	{
		XY now = q.front(); q.pop();
		XY next;

		for (int i = 0; i < 8; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;
			
			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			if (visited[next.y][next.x] || !map[next.y][next.x])
				continue;

			visited[next.y][next.x] = true;
			q.push(next);
		}
	}
}

// ���� �Է�
void input()
{
	cin >> garo >> sero;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> map[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	while (1)
	{
		// map, visited �ʱ�ȭ
		memset(map, 0, sizeof(map));
		memset(visited, 0, sizeof(visited));

		// �Է�
		input();

		// 0, 0�� �ԷµǸ� ����
		if (garo == 0 && sero == 0)
			break;

		int result = 0;
		// ��� ��ġ�� Ȯ���� ����
		for (int y = 0; y < sero; y++)
		{
			for (int x = 0; x < garo; x++)
			{
				// �湮�ߴ� ��ġ����, �ش� ��ġ�� ������ Ȯ��
				if (visited[y][x] || !map[y][x])
					continue;

				// ���� �մ´�.
				bfs({ y,x });
				// ���� ���� ����
				result++;
			}
		}
		cout << result << '\n';
	}
	return 0;
}
