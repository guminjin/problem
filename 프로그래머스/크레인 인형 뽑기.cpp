#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

#define endl '\n'

typedef long long ll;


int pickUp(vector<vector<int>> &board, int pickX)
{
	int n = board.size();

	for (int y = 0; y < n; y++)
	{
		if (board[y][pickX] == 0)
			continue;

		int pick = board[y][pickX];
		board[y][pickX] = 0;
		return pick;
	}
	return -1;
}
int solution(vector<vector<int>> board, vector<int> moves) {

	stack<int> st;

	for (int i = 0; i < moves.size(); i++)
	{
		int pickX = moves[i] - 1;
		int pick = pickUp(board, pickX);

		if (pick == -1)
			continue;

		if (!st.empty() && st.top() == pick)
			st.pop();
		else
			st.push(pick);
	}

	return st.size();
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	vector<vector<int>> board
		= { {0,0,0,0,0},
			{0,0,1,0,3},
			{0,2,5,0,1},
			{4,2,4,4,2},
			{3,5,1,3,1} };
	vector<int> moves = { 1, 5, 3, 5, 1, 2, 1, 4 };


	cout << solution(board, moves);


	return 0;
}
