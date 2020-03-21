#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 50 + 1;
const int MAX_POSSIBLE = 10 + 1;

struct XY
{
	int y, x;
};

struct INFO
{
	int y, x;
	int color;
	int time;
};

struct VISIT
{
	bool visit;
	int color;
	int time;
};

int garo, sero;
int redCnt, greenCnt;

int garden[MAX][MAX];
VISIT garVisited[MAX][MAX];

XY possible[MAX_POSSIBLE];
bool posVisited[MAX_POSSIBLE];
int possibleCnt;
bool copyPosVisited[MAX_POSSIBLE];

int result;

XY dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

void copyArray(int origin[][MAX], int copy[][MAX])
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			copy[y][x] = origin[y][x];
		}
	}
}

void print(int arr[][MAX])
{
	cout << endl;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cout << arr[y][x] << ' ';
		}
		cout << endl;
	}
}
void spreadGR()
{
	memset(garVisited, 0, sizeof(garVisited));
	
	int arr[MAX][MAX];
	copyArray(garden, arr);

	queue<INFO> q;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (arr[y][x] == 3 || arr[y][x] == 4)
			{				
				cout << &posVisited[12] << " " << &garVisited[y][x].visit << endl;
				garVisited[y][x].visit = true;
				garVisited[y][x].color = arr[y][x];
				garVisited[y][x].time = 0;
				
				q.push({ y, x, arr[y][x], 0 });
			}
		}
	}	

	int cnt = 0;
	while (!q.empty())
	{
		INFO now = q.front(); q.pop();
		INFO next;

		//print(arr);

		if (arr[now.x][now.y] == 5)
			continue;

		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i].x;
			next.y = now.y + dir[i].y;
			next.time = now.time + 1;
			next.color = now.color;

			if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
				continue;
			if (!arr[next.y][next.x])
				continue;
			if (garVisited[next.y][next.x].visit)
			{
				if (garVisited[next.y][next.x].time == next.time && garVisited[next.y][next.x].color != next.color)
				{
					arr[next.y][next.x] = 5;
					cnt++;
				}
				continue;
			}

			garVisited[next.y][next.x].visit = true;
			garVisited[next.y][next.x].color = next.color;
			garVisited[next.y][next.x].time = next.time;

			arr[next.y][next.x]= next.color;

			q.push(next);
		}
	}
	//cout << cnt;
	result = max(cnt, result);
}

void selectRed(int start, int cnt)
{
	if (cnt == redCnt)
	{
		for (int i = 0; i < possibleCnt; i++)
		{
			copyPosVisited[i] = posVisited[i];
		}

		spreadGR();

		for (int i = 0; i < possibleCnt; i++)
		{
			posVisited[i] = copyPosVisited[i];
		}
		return;
	}
	for (int i = start; i < possibleCnt; i++)
	{
		if (posVisited[i])
			continue;
		
		XY t = possible[i];

		garden[t.y][t.x] = 4;
		posVisited[i] = true;

		selectRed(i + 1, cnt + 1);

		garden[t.y][t.x] = 2;
		posVisited[i] = false;

	}
}

void selectGreen(int start, int cnt)
{
	if (cnt == greenCnt)
	{
		selectRed(0, 0);
		return;
	}
	for (int i = start; i < possibleCnt; i++)
	{
		if (posVisited[i])
			continue;

		XY t = possible[i];

		garden[t.y][t.x] = 3;
		posVisited[i] = true;

		selectGreen(i + 1, cnt + 1);

		garden[t.y][t.x] = 2;
		posVisited[i] = false;

	}
}

void solve()
{
	memset(posVisited, 0, sizeof(posVisited));
	selectGreen(0, 0);
	
	cout << result << '\n';
}

void input()
{
	cin >> sero >> garo >> greenCnt >> redCnt;

	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> garden[y][x];

			if (garden[y][x] == 1)
			{
				possible[possibleCnt++] = { y,x };
			}
		}

	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solve();
	
	return 0;
}
