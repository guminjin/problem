#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'
typedef long long ll;

const int MAX = 12 + 5;
const int CHESS_MAX = 10 + 5;

struct CHESS
{
	int y, x;
	int dir;
};
struct XY
{
	int y, x;
};

int n, k;
int map[MAX][MAX];
CHESS chess[CHESS_MAX];
vector<int> v[MAX][MAX];
XY dir[5] = { { 0, 0 } ,{ 0, 1 },{ 0, -1 },{ -1, 0 },{ 1, 0 } };

void print()
{
	cout << endl;

	for (int i = 1; i <= k; i++)
	{
		cout << i << "¹ø - y:" << chess[i].y << ", x:" << chess[i].x << ", dir:" << chess[i].dir << endl;
	}
	for (int y = 1; y <= n; y++)
	{
		for (int x = 1; x <= n; x++)
		{
			int s = v[y][x].size();
			if (s == 0)
				cout << "0\t";
			else
			{
				for (int i = 0; i < s; i++)
					cout << v[y][x][i] << ' ';
			}
			if (s == 1)
				cout << "\t";
			if (s == 2)
				cout << "    ";

		}
		cout << endl;
	}
}
// chess x,y range check
bool checkRange(XY lo)
{
	if (lo.x<1 || lo.y<1 || lo.y>n || lo.x>n)
		return false;
	return true;
}
// next chess location is blue or out of ragne
// change direction
void changeDir(int nowDir, int &nextDir)
{
	// change oposite diretion
	switch (nowDir)
	{
	case 1:
		nextDir = 2; break;
	case 2:
		nextDir = 1; break;
	case 3:
		nextDir = 4; break;
	case 4:
		nextDir = 3; break;
	}
}
// find chesses above moving chess
vector<int> findChess(XY now, int num)
{
	vector<int> move;
	int move_idx;
	int now_size = v[now.y][now.x].size();

	// find moving chess index
	for (int i = 0; i < now_size; i++)
	{
		if (v[now.y][now.x][i] == num)
		{
			move_idx = i;
			break;
		}
	}

	// find chesses above moving chess
	for (int i = move_idx; i < now_size; i++)
		move.push_back(v[now.y][now.x][i]);
	
	// remove finded chesses
	for (int i = 0; i < now_size - move_idx; i++)
		v[now.y][now.x].pop_back();

	return move;
}
// check next color and move chess
void checkNextColor(int color, XY next, vector<int> move)
{
	int size = move.size();
	// if white color, move in next location
	if (color == 0)
	{
		for (int i = 0; i < size; i++)
		{
			v[next.y][next.x].push_back(move[i]);
			chess[move[i]].y = next.y;
			chess[move[i]].x = next.x;
		}
	}
	// if red color, move in revers order
	else if (color = 1)
	{
		for (int i = size - 1; i >= 0; i--)
		{
			v[next.y][next.x].push_back(move[i]);
			chess[move[i]].y = next.y;
			chess[move[i]].x = next.x;
		}
	}
}
// move chess
void moveChess()
{
	for (int i = 1; i <= k; i++)
	{
		CHESS now = chess[i];
		CHESS next;

		next.y = now.y + dir[now.dir].y;
		next.x = now.x + dir[now.dir].x;
		next.dir = now.dir;

		int nextColor = map[next.y][next.x];
		// if next location is out of range or blue color 
		// change diretion and move location
		if (!checkRange({ next.y, next.x }) || nextColor == 2)
		{
			changeDir(now.dir, next.dir);
			next.y = now.y + dir[next.dir].y;
			next.x = now.x + dir[next.dir].x;

			nextColor = map[next.y][next.x];
			
			// if change location is not correct
			// change only direction
			if (!checkRange({ next.y, next.x }) || nextColor == 2)
			{
				next.y = now.y;
				next.x = now.x;
			}
			else
			{
				vector<int> move = findChess({ now.y, now.x }, i);
				checkNextColor(nextColor, { next.y, next.x }, move);
			}
		}
		else
		{
			vector<int> move = findChess({ now.y, now.x }, i);
			checkNextColor(nextColor, { next.y, next.x }, move);
		}
		chess[i] = next;
	}
}
void solution()
{
	int time = 0;

	while (time <= 1000)
	{
		//print();
		moveChess();
		time++;

		bool flg = false;
		for (int i = 1; i <= k; i++)
		{
			if (v[chess[i].y][chess[i].x].size() >= 4)
			{
				flg = true;
				break;
			}
		}
		if (flg)
		{
			cout << time << '\n';
			return;
		}
	}
	cout << "-1\n";
	return;
}
void input()
{
	cin >> n >> k;

	for (int y = 1; y <= n; y++)
		for (int x = 1; x <= n; x++)
			cin >> map[y][x];
	for (int i = 1; i <= k; i++)
	{
		CHESS ch;
		cin >> ch.y >> ch.x >> ch.dir;

		chess[i] = ch;
		v[ch.y][ch.x].push_back(i);
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	solution();

	return 0;
}