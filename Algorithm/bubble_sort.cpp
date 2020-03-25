#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

int main()
{
	int arr[10] = { 9, 2, 7, 8, 4, 3, 1, 5, 6, 0 };

	for (int i = 0; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if (arr[j] < arr[j - 1])
				swap(arr[j], arr[j - 1]);
		}
	}

	for (auto x : arr)
		cout << x << ' ';
	cout << '\n';
	return 0;
}