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

vector<int> solution(vector<string> gems) {
	vector<string> item;
	for (int i = 0; i < gems.size(); i++)
	{
		if (find(item.begin(), item.end(), gems[i]) == item.end())
			item.push_back(gems[i]);
	}

	map<string, int> m;
	for (int i = 0; i < item.size(); i++)
	{
		m[item[i]] = i;
	}

	vector<int> visit(item.size());
	int start = 0, end = 100;
	int l = 0, r = 0;
	int check = 0;
	bool flg = true;
	while (flg)
	{
		if (check == item.size())
		{
			if (r - l - 1 < end - start)
				start = l, end = r - 1;

			auto it = m.find(gems[l]);
			visit[it->second]--;
			if (visit[it->second] == 0)
				check--;
			l++;
			continue;
		}

		if (r >= gems.size())
		{
			while (1)
			{
				if (l >= gems.size())
					break;
				auto it = m.find(gems[l]);
				visit[it->second]--;
				if (visit[it->second] == 0)
					break;
				l++;
				continue;
			}
			flg = false;
			continue;
		}

		auto it = m.find(gems[r]);

		if (visit[it->second] == 0)
			check++;

		visit[it->second]++;
		r++;
	}

	vector<int> answer;
	answer.push_back(start + 1);
	answer.push_back(end + 1);
	return answer;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	vector<string> gems = { "XYZ", "XYZ", "XYZ" };
	vector<int> answer = solution(gems);
	for (auto x : answer)
	{
		cout << x << ' ';
	}
	return 0;
}
