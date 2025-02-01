#include<iostream>
#include"header.h"
using namespace std;
void sort(int * arr, int s,bool order)
{
	if (order == 1)
	{
		for (int i = 0; i < s - 1; i++)
		{
			for (int j = 0; j < (s - 1) - i; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					swap(arr[j], arr[j + 1]);
				}
			}
		}
	}
	else {
		for (int i = 0; i < s - 1; i++)
		{
			for (int j = 0; j < (s - 1) - i; j++)
			{
				if (arr[j] < arr[j + 1])
				{
					swap(arr[j], arr[j + 1]);
				}
			}
		}
	}
}
void find_highest(int arr[], int s, int position)
{
	if (position < s)
	{
		int i = 0;
		while (i<position-1)
		{
			i++;
		}
		cout << arr[i] << endl;
	}
}
void print(int arr[], int s)
{
	for (int i = 0; i < s ; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
