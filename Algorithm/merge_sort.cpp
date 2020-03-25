#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

const int MAX = 10;

// ����
void merge(int arr[MAX], int start, int end, int mid)
{
	// ���ĵ� �迭�� ����
	int temp[10];

	// A�迭�� ù��° �ε���
	int startS = start;
	// B�迭�� ù��° �ε���
	int startM = mid + 1;

	// temp�� �ε���
	int idx = 0;
	while (startS <= mid && startM <= end)
	{
		if (arr[startS] < arr[startM])
			temp[idx++] = arr[startS++];
		else
			temp[idx++] = arr[startM++];
	}

	// ������ �ϳ��� �迭�� ������ temp�� ����
	while (startS <= mid)
		temp[idx++] = arr[startS++];
	while (startM <= end)
		temp[idx++] = arr[startM++];

	// arr�迭���� start~end�ε����� ���ĵ� ���� ����
	for (int i = 0, j = start; i < idx, j <= end; i++, j++)
		arr[j] = temp[i];
}

// ����
void mergeSort(int arr[MAX], int start, int end)
{
	// ũ�Ⱑ 1�� �� �� ���� ����
	if (start < end)
	{
		int mid = (start + end) / 2;

		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);

		// ����
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