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

string solution(string compressed) 
{
	string input[1000];
	int inputIdx = 0;

	int len = compressed.length();
	string word = "";
	int num = 0;

	for (int i = 0; i < len; i++)
	{
		if (compressed[i] >= '0' && compressed[i] <= '9')
		{
			if (word != "")
			{
				input[inputIdx++] = word;
				word = "";
			}
			num = num * 10 + compressed[i] - '0';
		}
		else if (compressed[i] == ')')
		{
			if (word == "")
			{
				input[inputIdx++] = ")";
			}
			else
			{
				input[inputIdx++] = word;
				input[inputIdx++] = ")";

				word = "";
			}
		}
		else if (compressed[i] == '(')
		{
			if (word != "")
			{
				input[inputIdx++] = word;
				word = "";
			}
			if (num != 0)
			{
				input[inputIdx++] = to_string(num);
				num = 0;
			}
			if (num == 0)
			{
				input[inputIdx++] = "(";
			}
			else
			{
				input[inputIdx++] = to_string(num);
				input[inputIdx++] = "(";

				num = 0;
			}
		}
		else
		{
			if (num != 0)
			{
				input[inputIdx++] = to_string(num);
				num = 0;
			}
			word += compressed[i];
		}
	}
	if(word != "")
	{
		input[inputIdx++] = word;

		word = "";
	}

	string word2 = "";
	int n = 0;

	stack<string> st;
	for (int i = 0; i < inputIdx; i++)
	{
		string now = input[i];

		if (now == ")")
		{
			while (1)
			{
				string stTop = st.top(); st.pop();
				if (stTop[0] >= 'a' && stTop[0] <='z')
				{
					if (word2 != "")
					{
						string t = stTop;
						t += word2;
						word2 = t;
					}
					else
						word2 = stTop;
				}
				else if (stTop[0] == '(')
				{
					if (st.top()[0] >= '0' && st.top()[0] <= '9')
					{
						n = 0;
						for (int j = 0; j < st.top().length(); j++)
						{
							n = n * 10 + (st.top()[j] - '0');
						}

						string t = "";
						for (int j = 0; j < n; j++)
						{
							t += word2;
						}
						word2 = t;
					}
					else if (st.top()[0] >= 'a' && st.top()[0] <= 'z')
					{
						string t = st.top();
						t += word2;
						word2 = t;
					}

					st.pop();
					st.push(word2);
					word2 = "";
					break;
				}
			}
		}
		else
			st.push(now);
	}

	int stSize = st.size();
	string answer = "";
	for (int i = 0; i < stSize; i++)
	{
		string t = answer;
		answer = st.top();
		answer += t;
		st.pop();
	}
	return answer;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cout << solution("10p");

	return 0;
}
