#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

const int MAX = 10;

void quickSort(int arr[MAX], int start, int end)
{
	int pivot = arr[(start + end) / 2];
	int left = start;
	int right = end;

	// left와 right가 만날 때 까지 진행
	do
	{
		// arr[left]의 값이 pivot보다 작다면
		while (arr[left] < pivot)
			left++;
		// arr[right]의 값이 pivot보다 크다면
		while (arr[right] > pivot)
			right--;
		
		// arr[left]는 pivot보다 크고
		// arr[right]는 pivot보다 작으면
		// swap
		if (left <= right)
		{
			swap(arr[left], arr[right]);
			left++; right--;
		}
	} while (left <= right);

	// 크기가 1이 될때까지 나누면서 비교, 정렬
	if (left < end)
		quickSort(arr, left, end);
	if(right > start)
		quickSort(arr, start, right);
	
}
int main()
{
	int arr[10] = { 9, 2, 7, 8, 4, 3, 1, 5, 6, 0 };

	quickSort(arr, 0, MAX - 1);

	for (auto x : arr)
		cout << x << ' ';
	cout << '\n';
	return 0;
}