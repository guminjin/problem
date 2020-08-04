#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100 + 1;

struct INFO {
	int p;
	int cnt;
};

bool arr[MAX][MAX];
int n;
int per1, per2;

int result;

void bfs() {
	queue<INFO> q;
	q.push({ per1, 0 });

	while (!q.empty()) {
		INFO now = q.front(); q.pop();

		if (now.p == per2) {
			result = now.cnt;
			break;
		}

		for (int i = 1; i <= n; i++) {
			if (!arr[now.p][i])
				continue;

			arr[now.p][i] = false;
			arr[i][now.p] = false;

			q.push({ i, now.cnt + 1 });
		}
	}
}
void input() {
	cin >> n; 
	cin >> per1 >> per2;
	int rel;
	cin >> rel;
	for (int i = 0; i < rel; i++) {
		int a, b;
		cin >> a >> b;
		arr[a][b] = true;
		arr[b][a] = true;
	}

	result = -1;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	input();
	bfs();
	cout << result << '\n';
	return 0;
}
