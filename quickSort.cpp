#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

int Paritition1(int arr[], int start, int last)
{
	int pivot = arr[start];
	while (start<last)
	{
		while (start < last && arr[last] >= pivot)
		{
			--last;
		}
		arr[start] = arr[last];
		while (start < last && arr[start] <= pivot)
		{
			++start;
		}
		arr[last] = arr[start];
	}
	arr[start] = pivot;
	return start;
}
void QuickSort(int arr[], int start, int last)
{
	if (start < last)
	{
		int pivot = Paritition1(arr, start, last);
		QuickSort(arr, start, pivot - 1);
		QuickSort(arr, pivot + 1, last);
	}
}