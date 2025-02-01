#include<iostream>
#include "header.h"
using namespace std;

int sum(int array[],int n)
{
    int s=0;
    for(int i=0;i<n;i++)
    {
        s+=array[i];
    }
    return s;
}
int avg(int array[],int n)
{
    int s=sum(array,n);
    return s/n;
}
int max(int array[],int n)
{
    int m=array[0];
    for(int i=1;i<n;i++)
    {
        if(array[i]>m)
            m=array[i];
    }
    return m;
}
int min(int array[],int n)
{
    int m=array[0];
    for(int i=1;i<n;i++)
    {
        if(array[i]<m)
            m=array[i];
    }
    return m;   
}