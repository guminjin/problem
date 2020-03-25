#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

int main()
{
	int arr[10] = { 9, 2, 7, 8, 4, 3, 1, 5, 6, 0 };

	// 오름차순 정렬
	for (int i = 0; i < 10; i++)
	{
		// 최소값이 들어있는 인덱스변수
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