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


int main()
{
	 //buffer initalize
	char input[128] = { 0 , };
	cin.getline(input, 128);

	 //condition check
	if (strlen(input) >= 100)
		cout << "error\n";
	else
	{
		// only can use strlen() function
		for (int i = 0; i < strlen(input) / 2; i++)
		{
			input[127] = input[i];
			input[i] = input[strlen(input) - i - 1];
			input[strlen(input) - i - 1] = input[127];
		}

		input[strlen(input)] = NULL;

		// print final string
		cout << input;
	}

	return 0;
}

