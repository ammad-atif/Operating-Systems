#include<iostream>
#include "header.h"
using namespace std;
int main(int n,char*arg[])
{
    int j=1;
    int arr[n-1];
    for (int i = 0; i <n-1; i++,j++)
    {
        arr[i]=stoi(arg[j]);
    }
    // int arr[10]={1,2,4,53,12,34,64,12,15,10};
    cout<<"sum is "<<sum(arr,n-1)<<endl;
    cout<<"avg is "<<avg(arr,n-1)<<endl;
    cout<<"max is "<<max(arr,n-1)<<endl;
    cout<<"min is "<<min(arr,n-1)<<endl;
    


}