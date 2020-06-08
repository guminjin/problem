#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_DESK = 20 + 1;
const int MAX_PERSON = 1000 + 10;

struct INFO
{
	int idx;
	int doing;
};

struct PERSON
{
	int start;
	int recept;
	int repair;
};

int n, m, k;
int receptionNum, repairNum;
int reception[MAX_DESK];
int repair[MAX_DESK];
PERSON person[MAX_PERSON];
bool visit[2][MAX_DESK];

int result[2][MAX_PERSON];

void bfs()
{
	queue<INFO> recept;

	int idx = 1;
	while (1)
	{
		for (int i = idx; i <= k; i++)
		{
			if (person[i].start == 0)
			{
				recept.push({ i, -1 });
				idx = i;
			}
			else
				person[i].start--;
		}

		int receptSize = recept.size();
		for (int i = 0; i < receptSize; i++)
		{
			if(recept)
		}
		for (int i = 1; i <= n; i++)
		{
			if (visit[0][i])
				continue;


		}
	}
}
void input()
{
	cin >> n >> m >> k >> receptionNum >> repairNum;

	for (int i = 1; i <= n; i++)
		cin >> reception[i];

	for (int i = 1; i <= m; i++)
		cin >> repair[i];

	for (int i = 1; i <= k; i++)
		cin >> person[i].start;
}

void solve()
{
	input();
	bfs();
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		cout << '#' << tc << ' ' << '\n';
	}
	return 0;
}
