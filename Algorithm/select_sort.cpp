#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

int main()
{
	int arr[10] = { 9, 2, 7, 8, 4, 3, 1, 5, 6, 0 };

	// �������� ����
	for (int i = 0; i < 10; i++)
	{
		// �ּҰ��� ����ִ� �ε�������
		int mn_idx = i;
		for (int j = i; j < 10; j++)
		{
			if (arr[j] < arr[mn_idx])
				mn_idx = j;
		}
		swap(arr[mn_idx], arr[i]);
	}

	for (auto x : arr)
		cout << x << ' ';
	cout << '\n';
	return 0;
}