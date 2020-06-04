#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 20 + 2;
const int DESSERT_MAX = 100 + 1;

struct XY
{
	int y, x;
};

int n;
int m[MAX][MAX];
bool dessert[DESSERT_MAX];

// ↘, ↙, ↖, ↗ 이동방향
XY dir[4] = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };

// 이동할 수 있는 위치인지 확인
bool checkEatDessert(XY now)
{
	// x, y 범위 확인
	if (now.y < 0 || now.x < 0 || now.y >= n || now.x >= n)
		return false;
	// 이미 먹은 디저트인지 확인
	if (dessert[m[now.y][now.x]])
		return false;

	// 먹은 디저트 체크
	dessert[m[now.y][now.x]] = true;
	return true;
}

// 디저트 투어
bool eatDessert(XY start, int garo, int sero)
{
	int idx = 0;	// 이동방향 인덱스

	// ↘ 오른쪽 아래로 이동
	for (int i = 0; i < garo; i++)
	{
		start.y += dir[0].y;
		start.x += dir[0].x;

		// 위치 범위와 디저트 종류 체크
		if (!checkEatDessert(start))
			return false;
	}
	// ↙ 왼쪽 아래로 이동
	for (int i = 0; i < sero; i++)
	{
		start.y += dir[1].y;
		start.x += dir[1].x;
		if (!checkEatDessert(start))
			return false;
	}
	// ↖ 왼쪽 위로 이동
	for (int i = 0; i < garo; i++)
	{
		start.y += dir[2].y;
		start.x += dir[2].x;
		if (!checkEatDessert(start))
			return false;
	}
	// ↗ 오른쪽 위로 이동
	for (int i = 0; i < sero; i++)
	{
		start.y += dir[3].y;
		start.x += dir[3].x;
		if (!checkEatDessert(start))
			return false;
	}

	return true;
}

// 입력
void input()
{
	cin >> n;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			cin >> m[y][x];
		}
	}
}

int solve()
{
	// 결과값 저장
	int result = -1;

	// 입력
	input();

	// 0 ≤ y < n-2
	// 1 ≤ x < n-1
	// 해당 범위의 위치에서만 이동할 수 있음
	for (int y = 0; y < n-2; y++)
	{
		for (int x = 1; x < n-1; x++)
		{
			memset(dessert, 0, sizeof(dessert));

			// ↘, ↖ 이동횟수 : garo
			// ↙, ↗ 이동횟수 : sero
			for (int garo = 1; garo < n; garo++)
			{
				for (int sero = 1; sero < n; sero++)
				{
					// dessert 배열 초기화
					memset(dessert, 0, sizeof(dessert));

					// garo, sero의 크기로 사각형을 그릴수 있는지 확인
					if (eatDessert({ y,x }, garo, sero))
						// 최대값 갱신
						result = max(result, garo * 2 + sero * 2);
				}
			}
		}
	}

	return result;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		int result = solve();
		cout << '#' << tc << ' ' << result << '\n';
	}
	return 0;
}
