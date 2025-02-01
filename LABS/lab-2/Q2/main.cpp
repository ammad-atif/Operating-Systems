#include<iostream>
#include"header.h"
using namespace std;
int main()
{
	int arr[] = { 11,15,13,12,16,14,18,19,20,17 };
	int s = sizeof(arr) / sizeof(arr[0]);
	sort(arr,s, 0);
	print(arr,s);
	find_highest(arr, s, 4);
}
