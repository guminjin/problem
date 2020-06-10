#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// �Ѷ��� ��
	int tc; cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		char result = 'D';

		int aCnt, bCnt;

		// 4:��, 3:���׶��, 2:�׸�, 1:����
		int a[5] = { 0, };
		int b[5] = { 0, };

		// A�� ���� �Է�
		cin >> aCnt;
		for (int i = 0; i < aCnt; i++)
		{
			int k; cin >> k;
			a[k]++;
		}

		// B�� ���� �Է�
		cin >> bCnt;
		for (int i = 0; i < bCnt; i++)
		{
			int k; cin >> k;
			b[k]++;
		}

		// ���� ��翡 ���� ���� ��
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
