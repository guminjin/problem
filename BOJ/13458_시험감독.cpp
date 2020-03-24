#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int EXAM = 1000000;
const int PERSON = 1000000;

int person[PERSON];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// �������� �� �Է�
	int n; cin >> n;
	
	// �����帶�� �������� �� �Է�
	for (int i = 0; i < n; i++)
		cin >> person[i];
	
	// �Ѱ������� �ΰ������� ������ �� �ִ� ������ ��
	int b, c; cin >> b >> c;

	// �ּ� n���� �Ѱ������� �־���Ѵ�.
	ll result = n;
	for (int i = 0; i < n; i++)
	{
		// �Ѱ������� ������ �� �ִ� �������� ���� ����
		int num = person[i] - b;

		// �������� �� ������ 0�� �ȴٸ� �Ѱ��������θ� ���� ����
		// ������ �ΰ������� �ʿ�
		if (num > 0)
		{
			int mod = num % c;
			int div = num / c;

			// �ΰ������� ���� ����
			result += div;

			// �������� 0�� �ƴ϶�� �����ؾ��� �ο��� ���ұ⿡
			// �ΰ����� �Ѹ��� �� �߰�
			if (mod)
				result++;
		}
	}

	cout << result << '\n';
	return 0;
}
