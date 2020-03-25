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

	// left�� right�� ���� �� ���� ����
	do
	{
		// arr[left]�� ���� pivot���� �۴ٸ�
		while (arr[left] < pivot)
			left++;
		// arr[right]�� ���� pivot���� ũ�ٸ�
		while (arr[right] > pivot)
			right--;
		
		// arr[left]�� pivot���� ũ��
		// arr[right]�� pivot���� ������
		// swap
		if (left <= right)
		{
			swap(arr[left], arr[right]);
			left++; right--;
		}
	} while (left <= right);

	// ũ�Ⱑ 1�� �ɶ����� �����鼭 ��, ����
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