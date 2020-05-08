#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define endl '\n'

typedef long long ll;

set<string> result;

void dfs(int start, vector<vector<string>> group, vector<string> list)
{
	if (group.size() == start)
	{
		if (list.size() != group.size())
			return;

		string ch = "";
		sort(list.begin(), list.end());
		for (int i = 0; i < list.size(); i++)
		{
			ch += list[i];
		}
		result.insert(ch);
		return;
	}
	
	for (int j = 0; j < group[start].size(); j++)
	{
		bool flg = false;
		for (int k = 0; k < list.size(); k++)
		{
			if (list[k] == group[start][j])
			{
				flg = true;
				break;
			}
		}

		if (!flg)
		{
			vector<string> t = list;

			list.push_back(group[start][j]);
			dfs(start + 1, group, list);
			list = t;
		}
	}
}
bool compareString(string ban, string user)
{
	int banLen = ban.length();
	int userLen = user.length();

	if (banLen != userLen)
		return false;

	for (int i = 0; i < banLen; i++)
	{
		if (ban[i] == '*')
			continue;

		if (ban[i] != user[i])
			return false;
	}

	return true;
}
int solution(vector<string> user_id, vector<string> banned_id) 
{	
	vector<vector<string>> v(banned_id.size());

	for (int i = 0; i < banned_id.size(); i++)
	{
		for (int j = 0; j < user_id.size(); j++)
		{
			if (!compareString(banned_id[i], user_id[j]))
				continue;

			v[i].push_back(user_id[j]);
		}
	}
	for (int i = 0; i < v[0].size(); i++)
	{
		vector<string> list;
		list.push_back(v[0][i]);
		dfs(1, v, list);
	}
	return result.size();
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	vector<string> user_id = { "frodo", "fradi", "crodo", "abc123", "frodoc" };
	vector<string> banned_id = { "*rodo", "*rodo", "******" };

	cout << solution(user_id, banned_id) << '\n';

	return 0;
}
