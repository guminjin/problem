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


string solution(vector<int> numbers, string hand)
{
	string answer = "";

	int left = 9;
	int right = 11;

	for (int i = 0; i < numbers.size(); i++)
	{
		int num = numbers[i];
		if (num == 1 || num == 4 || num == 7)
		{
			answer += 'L';
			left = num - 1;
		}
		else if (num == 3 || num == 6 || num == 9)
		{
			answer += 'R';
			right = num - 1;
		}
		else
		{
			if (num == 0)
				num = 10;
			else
				num -= 1;
			int nx = num % 3;
			int ny = num / 3;

			int lx = left % 3;
			int ly = left / 3;

			int rx = right % 3;
			int ry = right / 3;

			int lLen = abs(nx - lx) + abs(ny - ly);
			int rLen = abs(nx - rx) + abs(ny - ry);

			if (lLen < rLen)
			{
				left = num;
				answer += 'L';
			}
			else if (lLen > rLen)
			{
				right = num;
				answer += 'R';
			}
			else
			{
				if (hand == "right")
				{
					right = num;
					answer += 'R';
				}
				else
				{
					left = num;
					answer += 'L';
				}
			}
			
		}
	}
	return answer;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	vector<int> numbers = { 7, 0, 8, 2, 8, 3, 1, 5, 7, 6, 2 };
	string hand = "left";

	cout << solution(numbers, hand);
	return 0;
}
