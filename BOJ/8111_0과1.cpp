#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define endl '\n'

typedef long long ll;

int x[10] = { 0, 1, 0, 7, 0, 0, 0, 3, 0, 9 };
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int tc; cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		string s; cin >> s;
		
		int firstNum = s[0] - '0';
		if (firstNum % 2 == 0)
		{
			cout << "BRAK\n";
			continue;
		}
		
	}
	return 0;
}
