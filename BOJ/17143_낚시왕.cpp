#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 100;

struct SHARK
{
	int s;
	int d;
	int z;
};

int garo, sero, shark;
SHARK map[2][MAX][MAX];

int result;

void moveFish()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			map[1][y][x].z = 0;
			map[1][y][x].s = 0;
			map[1][y][x].d = 0;
		}
	}

	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (!map[0][y][x].z)
				continue;

			switch (map[0][y][x].d)
			{
			// 위로 이동, y감소
			case 1:
				int ny = (((sero - 1) * 2) - y) + map[0][y][x].s;
				ny = ny % ((sero - 1) * 2);

				int nd = 2;
				if (ny >= (sero - 1))
				{
					ny = ((r - 1) * 2) - ny;
				}
				break;
			// 아래로 이동, y증가
			case 2:
				break;
			// 오른쪽 이동, x증가
			case 3:
				break;
			// 왼쪽 이동, x감소
			case 4:
				break;
			}
		}
	}
}

void solve()
{
	for (int i = 0; i < garo; i++)
	{
		for (int y = 0; y < sero; y++)
		{
			if (!map[0][y][i].z)
				continue;

			result += map[0][y][i].z;
			map[0][y][i].z = 0;
			map[0][y][i].s = 0;
			map[0][y][i].d = 0;
			break;
		}

		moveFish();
	}
}

void input()
{
	cin >> sero >> garo >> shark;
	for (int i = 0; i < shark; i++)
	{
		int x, y;
		int s, d, z;
		cin >> y >> x >> s >> d >> z;

		map[0][y][x].s = s;
		map[0][y][x].d = d;
		map[0][y][x].z = z;
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	return 0;
}
