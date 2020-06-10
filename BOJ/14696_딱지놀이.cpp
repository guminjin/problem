#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// 총라운드 수
	int tc; cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		char result = 'D';

		int aCnt, bCnt;

		// 4:별, 3:동그라미, 2:네모, 1:세모
		int a[5] = { 0, };
		int b[5] = { 0, };

		// A의 딱지 입력
		cin >> aCnt;
		for (int i = 0; i < aCnt; i++)
		{
			int k; cin >> k;
			a[k]++;
		}

		// B의 딱지 입력
		cin >> bCnt;
		for (int i = 0; i < bCnt; i++)
		{
			int k; cin >> k;
			b[k]++;
		}

		// 딱지 모양에 따른 개수 비교
		for (int i = 4; i > 0; i--)
		{
			if (a[i] == b[i])
				continue;
			else if (a[i] > b[i])
			{
				result = 'A';
				break;
			}
			else if (a[i] < b[i])
			{
				result = 'B';
				break;
			}
		}
		cout << result << '\n';
	}
	return 0;
}
