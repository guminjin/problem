#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100000 + 5;
const int INF = 987654321;

struct INFO
{
	int x;
	int time;
};

int n, k;
int visited[MAX];

// ���� Ȯ��
bool checkRange(INFO next)
{
	// ���� Ȯ��
	if (next.x<0 || next.x>=MAX)
		return false;

	// �ش� ��ġ�� ���������� �ð�Ȯ��
	if (visited[next.x] <= next.time)
		return false;

	return true;
}

void bfs()
{
	queue<INFO> q;
	q.push({ n, 0 });
	visited[n] = 0;

	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		if (now.x == k)
			continue;

		// x + 1, x - 1, x * 2 ������ ���� Ȯ��
		INFO next[3] = { { now.x * 2, now.time } ,
						 { now.x + 1, now.time + 1 }, 
						 { now.x - 1, now.time + 1 }
					   };

		for (int i = 0; i < 3; i++)
		{
			if (!checkRange(next[i]))
				continue;

			// �ش� ��ġ�� ������ �ð� ����
			visited[next[i].x] = next[i].time;
			q.push(next[i]);
		}
	}

}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	for (int i = 0; i < MAX; i++)
		visited[i] = INF;

	// �Է�
	cin >> n >> k;
	bfs();
	cout << visited[k] << '\n';

	return 0;
}
