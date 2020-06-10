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

typedef long long ll;\

int a, b, c, num;

bool check()
{
	// a, b, c�� ������ �л��� ���� ���������� Ȯ��
	if (num%a == 0 || num % b == 0 || num % c == 0)
		return true;
	else
	{
		// c�� ���� �� ���� ū ��
		int divC = num / c;		

		// c�� �ִ� �� �������� 0���� Ȯ��
		for (int i = divC; i >= 0; i--)
		{
			// c�� ���� i�� ������� �� ���� �л� ��
			int modC = num - (c*i);

			// b�� ���� �� ���� ū ��
			int divB = modC / b;	

			// b�� �ִ� �� �������� 0���� Ȯ��
			for (int j = divB; j >= 0; j--)
			{
				int modB;

				// b�� ���������� ���� ���
				if (divB == 0)
					modB = modC;
				else
					modB = modC - (b*j);

				if (modB%a == 0)
					return true;
			}
		}
	}
	return false;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> a >> b >> c >> num;	

	cout << check() << '\n';
	return 0;
}
