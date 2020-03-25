#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

const int MAX = 10;

// 병합
void merge(int arr[MAX], int start, int end, int mid)
{
	// 정렬된 배열을 저장
	int temp[10];

	// A배열의 첫번째 인덱스
	int startS = start;
	// B배열의 첫번째 인덱스
	int startM = mid + 1;

	// temp의 인덱스
	int idx = 0;
	while (startS <= mid && startM <= end)
	{
		if (arr[startS] < arr[startM])
			temp[idx++] = arr[startS++];
		else
			temp[idx++] = arr[startM++];
	}

	// 나머지 하나의 배열의 끝까지 temp에 삽입
	while (startS <= mid)
		temp[idx++] = arr[startS++];
	while (startM <= end)
		temp[idx++] = arr[startM++];

	// arr배열에서 start~end인덱스에 정렬된 값을 삽입
	for (int i = 0, j = start; i < idx, j <= end; i++, j++)
		arr[j] = temp[i];
}

// 분할
void mergeSort(int arr[MAX], int start, int end)
{
	// 크기가 1이 될 때 까지 나눔
	if (start < end)
	{
		int mid = (start + end) / 2;

		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);

		// 병합
		merge(arr, start, end, mid);
	}
}
int main()
{
	int arr[10] = { 9, 2, 7, 8, 4, 3, 1, 5, 6, 0 };

	mergeSort(arr, 0, MAX - 1);

	for (auto x : arr)
		cout << x << ' ';
	cout << '\n';
	return 0;
}