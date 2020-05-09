#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;

char priority[6][3] = { { '+', '-', '*' },{ '+', '*', '-' },
						{ '-', '+', '*' },{ '-', '*', '+' },
						{ '*', '+', '-' },{ '*','-', '+' } };

int findParent(int idx, vector<int> parent)
{
	if (parent[idx] == idx)
		return idx;
	findParent(parent[idx], parent);
}

ll solution(string expression) {
	vector<int> numbers;
	vector<char> opers;
	for (int i = 0; i < expression.length(); i++)
	{
		int num = 0;
		while (1)
		{
			if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*')
			{
				opers.push_back(expression[i]);
				break;
			}

			num = num * 10;
			num += (expression[i] - '0');
			if (++i >= expression.length())
				break;
		}
		numbers.push_back(num);
	}

	sort(opers.begin(), opers.end());
	do
	{
		vector<int> parent(numbers.size());
		vector<int> t(numbers.size());
		t = numbers;

		for (int i = 0; i < t.size(); i++)
			parent[i] = i;

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < opers.size(); k++)
				{
					if (priority[i][j] == opers[k])
					{
						int idxA = findParent(t[i], parent);
						int idxB = findParent(t[i + 1], parent);
						
						if (idxA != i)
						{
							parent[i] = idxA;
						}
						if (idxB != i + 1)
						{
							parent[i] = idxB;
						}

						ll a = t[idxA];
						ll b = t[idxB];

						switch (priority[i][j])
						{
						case '+':
							t[idx]
							break;
						case '-':
							break;
						case '*':
							break;

						}
					}
				}
			}
		}

	} while (next_permutation(opers.begin(), opers.end()));


	return answer;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	string expression = "100-200*300-500+20";
	cout << solution(expression);

	return 0;
}
