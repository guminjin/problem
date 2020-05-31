#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <cstring>
using namespace std;

#define endl '\n'
typedef long long ll;

const int MAX = 10 + 1;
const int MAX_SEC = 100 + 1;
const int MAX_BC = 8 + 1;

// BC의 중심 위치, 범위, 성능
struct BC
{
	int y, x;
	int len;
	int power;
};

// m의 정보
struct MAP_INFO
{
	int idx;
	int power;

	bool operator< (MAP_INFO m) const
	{
		return power > m.power;
	}
};

struct INFO
{
	int y, x;
	int len;
};

int sec, bcCnt;					// 초, BC의 개수
vector<MAP_INFO> m[MAX][MAX];	// 지도	
int personA[MAX_SEC];			// A의 이동경로
int personB[MAX_SEC];			// B의 이동경로
BC bc[MAX_BC];					// 각각의 BC의 정보

int X[5] = { 0, 0, 1, 0, -1 };	// 1:상, 2:우, 3:하, 4:좌 
int Y[5] = { 0,-1, 0, 1, -0 };

bool visit[MAX][MAX];			// 방문 확인

int moveAB()
{
	// A와 B의 시작위치 초기화
	int yA = 1, xA = 1;
	int yB = 10, xB = 10;

	// 충전량
	int sumA = 0, sumB = 0;

	// sec초 까지 이동
	for (int i = 0; i <= sec; i++)
	{
		yA += Y[personA[i]];
		xA += X[personA[i]];

		yB += Y[personB[i]];
		xB += X[personB[i]];

		// A와 B의 위치에서 배열의 크기가 둘 다 0이 아닐 때
		if (m[yA][xA].size() && m[yB][xB].size())
		{
			// 해당 위치의 0번째 배열에서 BC의 idx가 같을 때
			if (m[yA][xA][0].idx == m[yB][xB][0].idx)
			{
				// A, B 위치의 배열의 크기가 1이라면
				// 같은 BC를 공유하므로 power / 2를 각각의 충전량에 더한다.
				if (m[yA][xA].size() == 1 && m[yB][xB].size() == 1)
				{
					sumA += m[yA][xA][0].power / 2;
					sumB += m[yB][xB][0].power / 2;
				}

				// B의 위치의 배열의 크기가 1이라면
				// B의 충전량에는 해당 위치의 0번째 인덱스의 power를 더하고,
				// A의 충전량에는 해다 위치의 1번째 인덱스의 power를 더한다.
				else if (m[yB][xB].size() == 1)
				{
					sumA += m[yA][xA][1].power;
					sumB += m[yB][xB][0].power;
				}

				// A의 위치의 배열의 크기가 1이라면
				// A의 충전량에는 해당 위치의 0번째 인덱스의 power를 더하고,
				// B의 충전량에는 해다 위치의 1번째 인덱스의 power를 더한다.
				else if (m[yA][xA].size() == 1)
				{
					sumA += m[yA][xA][0].power;
					sumB += m[yB][xB][1].power;
				}

				// A, B위치의 배열의 크기가 모두 2이상이라면
				else
				{
					// 1번째 인덱스의 power를 비교해서 각각의 power를 더한다.
					if (m[yA][xA][1].power >= m[yB][xB][1].power)
					{
						sumA += m[yA][xA][1].power;
						sumB += m[yB][xB][0].power;
					}
					else if (m[yA][xA][1].power < m[yB][xB][1].power)
					{
						sumA += m[yA][xA][0].power;
						sumB += m[yB][xB][1].power;
					}
				}
			}

			// 해당 위치의 0번째 배열에서 BC의 idx가 다를 떼
			else
			{
				sumA += m[yA][xA][0].power;
				sumB += m[yB][xB][0].power;
			}

		}

		// A와 B의 위치에서 배열의 크기가 0일 때
		else
		{
			if (m[yA][xA].size())
			{
				sumA += m[yA][xA][0].power;
			}
			if (m[yB][xB].size())
			{
				sumB += m[yB][xB][0].power;
			}
		}
	}
	return sumA + sumB;
}

// 각각의 BC의 중심에서 범위 찾기
void bfs()
{
	for (int i = 1; i <= bcCnt; i++)
	{
		BC nowBC = bc[i];

		queue<INFO> q;
		q.push({ nowBC.y, nowBC.x, 0 });
		m[nowBC.y][nowBC.x].push_back({ i, nowBC.power });

		memset(visit, 0, sizeof(visit));
		visit[nowBC.y][nowBC.x] = true;

		// BC[i]가 영향을 주는 범위 찾기
		while (!q.empty()) 
		{
			INFO now = q.front(); q.pop();

			// 범위 확인
			if (now.len >= nowBC.len)
				continue;

			// 상, 우, 하, 좌 네방향 모두 확인
			for (int j = 1; j < 5; j++)
			{
				INFO next;
				next.y = now.y + Y[j];
				next.x = now.x + X[j];
				next.len = now.len + 1;

				// 범위 체크
				if (next.y <= 0 || next.x <= 0 || next.y > 10 || next.x > 10)
					continue;
				// 방문 체크
				if (visit[next.y][next.x])
					continue;

				// m에 BC의 번호와 power 푸시
				m[next.y][next.x].push_back({ i, nowBC.power });
				// 방문 처리
				visit[next.y][next.x] = true;
				q.push(next);
			}
		}
	}

	// m을 power를 기준으로 내림차순 정렬
	for (int y = 1; y < MAX; y++)
	{
		for (int x = 1; x < MAX; x++)
		{
			if (!m[y][x].size())
				continue;
			else
				sort(m[y][x].begin(), m[y][x].end());
		}
	}
}

// 입력
void input()
{
	for (int y = 1; y < MAX; y++)
	{
		for (int x = 1; x < MAX; x++)
			m[y][x].clear();
	}

	cin >> sec >> bcCnt;

	// 출발 위치인 0초 부터 충전량 측정
	personA[0] = personB[0] = 0;
	for (int i = 1; i <= sec; i++)
		cin >> personA[i];
	for (int i = 1; i <= sec; i++)
		cin >> personB[i];

	// BC의 정보 입력
	for (int i = 1; i <= bcCnt; i++)
	{
		int y, x, length, power;
		cin >> x >> y >> length >> power;
		bc[i] = { y, x, length, power };
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	freopen("input.txt", "r", stdin);

	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++)
	{
		input();
		bfs();
		cout << '#' << t << ' ' << moveAB() << '\n';
	}
	return 0;
}