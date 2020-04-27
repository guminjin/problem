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
	// visited 배열 초기화
	memset(visited, 0, sizeof(visited));

	bool flg = false;	// 찾은 키가 있는지 확인하는 변수
	
	queue<XY> q;
	q.push({ 0, 0 });
	
	while (!q.empty())
	{
		XY now = q.front(); q.pop();
		XY next;

		// 상하좌우 네방향을 모두 확인
		for (int i = 0; i < 4; i++)
		{
			next.y = now.y + dir[i].y;
			next.x = now.x + dir[i].x;

			// 범위 확인
			if (next.y<0 || next.x<0 || next.y>sero + 1 || next.x>garo + 1)
				continue;
			// * : 벽 -> 지나갈 수 없다.
			if (map[next.y][next.x] == '*')
				continue;
			// 방문한 위치 체크
			if (visited[next.y][next.x])
				continue;
			// 해당 위치가 키라면
			if (map[next.y][next.x] >= 'a' && map[next.y][next.x] <= 'z')
			{
				int idx = map[next.y][next.x] - 'a';
				
				// 키가 있다고 표시
				if(!key[idx])
					key[idx] = true;

				// 키의 위치를 .으로 바꿔줌
				map[next.y][next.x] = '.';

				// 키를 찾았음을 표시
				flg = true;
			}

			// 문이라면
			if (map[next.y][next.x] >= 'A' && map[next.y][next.x] <= 'Z')
			{
				int idx = tolower(map[next.y][next.x]) - 'a';

				// 키가 없다면
				if (!key[idx])
					continue;
				// 키가 있다면 해당 문을 열 수 있다.
				// .으로 바꿔줌
				else
					map[next.y][next.x] = '.';
			}
			
			// 문서를 찾음
			if (map[next.y][next.x] == '$')
			{
				result++;

				// .으로 바꿔서 중복 제거
				map[next.y][next.x] = '.';
			}

			visited[next.y][next.x] = true;
			q.push(next);
		}
	}
	return flg;
}

// 초기화, 입력
void input()
{
	// 초기화
	memset(map, 0, sizeof(map));
	memset(key, 0, sizeof(key));
	result = 0;

	// 입력
	cin >> sero >> garo;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			char c; cin >> c;
			map[y][x] = c;
		}
	}
	
	// 가지고 있는 키 확인
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
