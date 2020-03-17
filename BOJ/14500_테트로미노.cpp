#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 500 + 1;
const int MAX_SHAPE = 15;

struct XY
{
	int y, x;
};

int garo, sero;
int mx;
int paper[MAX][MAX];
bool visited[MAX][MAX];
XY dir[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

void check(XY start)
{
	int shapeX[4][4];
	int shapeY[4][4];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			shapeX[i][j] = shapeY[i][j] = 0;

	shapeX[0][1] = 1;
	shapeX[0][2] = 2;
	shapeX[0][3] = 1; shapeY[0][3] = 1;

	shapeX[1][1] = 1;
	shapeX[1][2] = 2;
	shapeX[1][3] = 1; shapeY[1][3] = -1;

	shapeY[2][1] = 1;
	shapeY[2][2] = 2;
	shapeY[2][3] = 1; shapeX[2][3] = 1;

	shapeY[3][1] = 1;
	shapeY[3][2] = 2;
	shapeY[3][3] = 1; shapeX[3][3] = -1;

	for (int i = 0; i < 4; i++)
	{
		int flg = true;
		XY next[4];
		int sum = 0;
		for (int j = 0; j < 4; j++)
		{
			next[j].y = start.y + shapeY[i][j];
			next[j].x = start.x + shapeX[i][j];

			if (next[j].x<1 || next[j].y<1 || next[j].x>garo || next[j].y>sero)
			{
				flg = false;
				break;
			}
			sum += paper[next[j].y][next[j].x];
		}

		if (flg && sum > mx)
			mx = sum;
	}
}
void dfs(XY start, XY now, int cnt, int sum)
{
	if (cnt == 4 )
	{
		if(mx < sum)
			mx = sum;
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		XY next;
		next.y = now.y + dir[i].y;
		next.x = now.x + dir[i].x;

		if (next.x<1 || next.y <1 || next.x>garo || next.y >sero)
			continue;
		if (visited[next.y][next.x])
			continue;

		visited[next.y][next.x] = true;
		sum += paper[next.y][next.x];

		dfs(start, next, cnt + 1, sum);

		visited[next.y][next.x] = false;
		sum -= paper[next.y][next.x];
	}
	
}
void solution()
{
	int sum = 0;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			check({ y,x });

			visited[y][x] = true;
			sum += paper[y][x];

			dfs({ y, x }, { y, x }, 1, sum);

			visited[y][x] = false;
			sum -= paper[y][x];
		}
	}

	cout << mx << '\n';
}
void input()
{
	cin >> sero >> garo;
	for (int y = 1; y <= sero; y++)
	{
		for (int x = 1; x <= garo; x++)
		{
			cin >> paper[y][x];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solution();

	return 0;
}
