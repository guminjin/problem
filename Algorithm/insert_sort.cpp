#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

int main()
{
	int arr[10] = { 9, 2, 7, 8, 4, 3, 1, 5, 6, 0 };

	for (int i = 1; i < 10; i++)
	{
		int idx = i - 1;
		int value = arr[i];

		while (idx >= 0 && value < arr[idx])
		{
			swap(arr[idx], arr[idx+ 1]);
			idx--;
		}
		arr[idx + 1] = value;
	}

	for (auto x : arr)
		cout << x << ' ';
	cout << '\n';
	return 0;
}