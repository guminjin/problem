#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define endl '\n'

typedef long long ll;

vector<int> solution(string s) {
	vector<int> answer;

	// 튜플의 개수
	int sLen = s.length();
	int groupSize = 0;
	for (int i = 0; i < sLen - 1; i++)
	{
		if (s[i] == '{')
			groupSize++;
	}

	// 각각의 튜플 구하기
	int idx = 0;
	vector<vector<int>> v(groupSize);
	for (int i = 0; i < sLen - 1; i++)
	{
		if (s[i] -'0' >=0 && s[i] - '0' <=9)
		{
			int num = 0;
			while (1)
			{
				num *= 10;
				num += s[i] - '0';
				i++;

				if (s[i] == '}' || s[i] == ',')
					break;
			}
			v[idx].push_back(num);

			if (s[i] == '}')
				idx++;
		}
	}

	// 튜플의 각각 사이즈
	vector<int> vSize;
	for (int i = 0; i < groupSize; i++)
	{
		vSize.push_back(v[i].size());
	}
	sort(vSize.begin(), vSize.end());

	// 튜플을 크기로 정렬
	vector<vector<int>> t(groupSize);
	for (int i = 0; i < vSize.size(); i++)
	{
		idx = 0;
		while (1)
		{
			if (v[idx].size() == vSize[i])
			{
				t[i] = v[idx];
				v[idx].clear();
				break;
			}
			idx++;
		}
	}

	for (int i = 0; i < t.size(); i++)
	{
		for (int j = 0; j < t[i].size(); j++)
		{
			bool flg = false;
			for (int k = 0; k < answer.size(); k++)
			{
				if (answer[k] == t[i][j])
					flg = true;
			}

			if (!flg)
				answer.push_back(t[i][j]);
		}
	}

	return answer;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	string s; cin >> s;
	solution(s);
	
	return 0;
}
