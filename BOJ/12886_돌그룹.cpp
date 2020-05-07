#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

// a, b, c의 최대값 
const int MAX = 500 + 1;

struct INFO
{
	int a, b, c;
};

int a, b, c;
int result = -1;
int visit[MAX][MAX];

// 세개의 수를 정렬해준다.
// a < b < c
void valueCompare(int &a, int &b, int &c)
{
	// 최솟값
	int mn = min(a, min(b, c));
	// 최대값
	int mx = max(a, max(b, c));
	// 중간값
	int mid = a + b + c - mn - mx;

	a = mn;
	b = mid;
	c = mx;
}

// bfs
int solve()
{
	queue<INFO> q;
	q.push({ a, b, c });

	// a, b, c 정렬
	valueCompare(a, b, c);
	// 방문처리
	visit[a][b] = true;

	// q가 비었으면 종료 => 같은 수로 만들 수 없다.
	while (!q.empty())
	{
		INFO now = q.front(); q.pop();

		// a = b = c라면 종료
		if (now.a == now.b && now.b == now.c)
			return 1;

		// a, b, c로 만들 수 있는 세가지 경우의 수
		INFO next[3] = { {now.a*2, now.b, now.c- now.a},
						 { now.a*2, now.b- now.a, now.c},
						 { now.a, now.b*2, now.c- now.b}
						};

		for (int i = 0; i < 3; i++)
		{
			INFO n = next[i];
			// 정렬
			valueCompare(n.a, n.b, n.c);

			// 방문확인
			if (visit[n.a][n.b])
				continue;

			// 방문처리 후 큐에 푸시
			visit[n.a][n.b] = true;
			q.push(n);
		}
	}
	return 0;
}

// 입력
void input()
{
	int sum = 0;
	cin >> a >> b >> c;
	sum = a + b + c;

	// sum이 3으로 나누어떨어지지 않으면
	// a, b, c가 모두 같은 수가 될 수 없다.
	if (sum % 3 == 0)
		result = 0;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();

	// 3으로 나누어떨어지지 않음
	if (result == -1)
		cout << "0\n";
	else
		cout << solve() << '\n';
	
	return 0;
}
