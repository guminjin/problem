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
TURN turn[6];		// 연산 저장
int result = INF;

// 오른쪽 -> 아래 -> 왼쪽 -> 위
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

// 배열의 최솟값을 찾는다.
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

// 연산을 수행
void turnArr(TURN now)
{
	int startY = now.startY;
	int startX = now.startX;
	int endY = now.endY;
	int endX = now.endX;

	while (1)
	{
		// 시계방향으로 돌면서 배열의 값을 저장
		vector<int> v;

		// 오른쪽으로 먼저 가는데
		// 시작부터 X[i]의 값을 더하고 시작하기때문에
		// nx의 값을 1 빼준다.
		int ny = startY;
		int nx = startX - 1;
		int len = endX - startX + 1;
		int l = len;

		// 시계방향으로 돌면서 값을 저장
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < l; j++)
			{
				ny += Y[i];
				nx += X[i];

				v.push_back(mem[ny][nx]);
			}
			
			// 크기가 4일때 아래처럼 i방향으로 이동한다.
			// 따라서 i가 0 또는 2일 때 len을 -1해준다.
			//	0 0 0 0
			//	3 . . 1
			//	3 . . 1
			//	2 2 2 1
			if (i == 0 || i == 2)
				l--;
		}

		// v의 사이즈를 이용해 rotate 시켜준다.
		int size = v.size();
		rotate(v.begin(), v.begin() + size - 1, v.end());


		// 다시 원래 있던 자리에 한칸씩 이동한 결과를 넣어준다.
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
		
		// 같은 위치면 더 이상 회전시킬 수 없다.
		if (startX == endX && startY == endY)
			break;
	}
}

// 배열 복사
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

// 회전의 순서를 임의로 지정
void dfs(int cnt)
{
	// 모든 회전을 수행했다면
	if (cnt == k)
	{
		// 배열의 최솟값을 찾는다.
		findMin();
		return;
	}
	for (int i = 0; i < k; i++)
	{
		// 이미 수행한 연산 체크
		if (turn[i].visit)
			continue;
		
		// 현재 배열을 temp에 저장해둔다.
		int temp[MAX][MAX];
		copyArr(mem, temp);

		// 연산을 수행
		turnArr(turn[i]);
		// 해당 연산을 수행했다고 체크
		turn[i].visit = true;

		// cnt를 1증가하고 다음 연산을 찾는다.
		dfs(cnt + 1);
		
		// 해당 연산을 수행하지 않았다고 체크
		turn[i].visit = false;
		// 해당 연산을 수행하기 이전 상태로 되돌린다.
		copyArr(temp, mem);
	}
}


void solve()
{
	// 회전의 순서는 임의로 지정
	dfs(0);

	// 배열의 최솟값 출력
	cout << result << '\n';
}

// 입력
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
