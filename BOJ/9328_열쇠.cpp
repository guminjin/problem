#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 2;

struct XY
{
	int y, x;
};

int garo, sero;
char map[MAX][MAX];
bool key[26];
bool visited[MAX][MAX];
XY dir[4] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
int result;

bool bfs()
{
	// visited �迭 �ʱ�ȭ
	memset(visited, 0, sizeof(visited));

	bool flg = false;	// ã�� Ű�� �ִ��� Ȯ���ϴ� ����
	
	queue<XY> q;
	q.push({ 0, 0 });
	
	while (!q.empty())
	{
		XY now = q.front(); q.pop();
		XY next;

		// �����¿� �׹����� ��� Ȯ��
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + dir[i].y;
			next.x = now.x + dir[i].x;

			// ���� Ȯ��
			if (next.y<0 || next.x<0 || next.y>sero + 1 || next.x>garo + 1)
				continue;
			// * : �� -> ������ �� ����.
			if (map[next.y][next.x] == '*')
				continue;
			// �湮�� ��ġ üũ
			if (visited[next.y][next.x])
				continue;
			// �ش� ��ġ�� Ű���
			if (map[next.y][next.x] >= 'a' && map[next.y][next.x] <= 'z')
			{
				int idx = map[next.y][next.x] - 'a';
				
				// Ű�� �ִٰ� ǥ��
				if(!key[idx])
					key[idx] = true;

				// Ű�� ��ġ�� .���� �ٲ���
				map[next.y][next.x] = '.';

				// Ű�� ã������ ǥ��
				flg = true;
			}

			// ���̶��
			if (map[next.y][next.x] >= 'A' && map[next.y][next.x] <= 'Z')
			{
				int idx = tolower(map[next.y][next.x]) - 'a';

				// Ű�� ���ٸ�
				if (!key[idx])
					continue;
				// Ű�� �ִٸ� �ش� ���� �� �� �ִ�.
				// .���� �ٲ���
				else
					map[next.y][next.x] = '.';
			}
			
			// ������ ã��
			if (map[next.y][next.x] == '$')
			{
				result++;

				// .���� �ٲ㼭 �ߺ� ����
				map[next.y][next.x] = '.';
			}

			visited[next.y][next.x] = true;
			q.push(next);
		}
	}
	return flg;
}

// �ʱ�ȭ, �Է�
void input()
{
	// �ʱ�ȭ
	memset(map, 0, sizeof(map));
	memset(key, 0, sizeof(key));
	result = 0;

	// �Է�
	cin >> sero >> garo;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c;
		}
	}
	
	// ������ �ִ� Ű Ȯ��
	string s; cin >> s;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '0')
			break;

		int idx = s[i] - 'a';
		key[idx] = true;
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int tc; cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		input();

		while (1)
		{
			if (!bfs())
				break;
		}

		cout << result << '\n';
	}
	return 0;
}
