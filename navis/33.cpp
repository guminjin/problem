#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;

map<int, int> m;

int solution(int num, vector<int> mark) {

	int markSize = mark.size();
	int startPerson;
	int startIdx, endIdx;

	bool flg = true;
	for (int i = 0; i < markSize; i++)
	{
		if (m[mark[i]] == 0)
		{
			m[mark[i]]++;
		}
		else
		{
			startPerson = mark[i];
			endIdx = i - 1;
			flg = false;
			break;
		}
	}

	if (flg)
	{

	}
	else
	{
		for (int i = 0; i < endIdx; i++)
		{
			num--;

			if (mark[i] == startPerson)
			{
				startIdx = i;
				break;
			}

		}
		int mod = endIdx - startIdx + 1;
		if (mod < num)
			mod = num % mod;
		else
			mod = num;

		return mark[startIdx + mod];
	}

	

}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int num = 10;
	vector<int> mark = { 1,2,3,1 };
	cout << solution(num, mark) << endl;
	return 0;
}
