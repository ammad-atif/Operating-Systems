#include <cmath>
#include <cstddef>
#include <iostream>
#include <pthread.h>
using namespace std;

int **arr;
int r;
int c;

void *func(void *arg)
{
    int *x = (int *)arg;
    int *res = new int(0);
    for (int i = r - 1; i >= 0; i--)
    {
        if (arr[i][*x])
        {
            *res += pow(2, (r - 1) - i);
        }
    }

    delete x;
    pthread_exit((void *)res);
}

int main(int argc, char const *argv[])
{
    cout << "Enter number of rows: " << endl;
    cin >> r;
    cout << "Enter numebr of columns: " << endl;
    cin >> c;
    arr = new int *[r];
    for (int i = 0; i < r; i++)
    {
        arr[i] = new int[c];
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << "Enter " << i + 1 << j + 1 << " element of array" << endl;
            cin >> arr[i][j];
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    pthread_t t[c];
    int res[c];
    int *result;

    for (size_t i = 0; i < c; i++)
    {
        int *x = new int;
        *x = i;
        pthread_create(&t[i], NULL, &func, (void *)x);
    }

    for (size_t i = 0; i < c; i++)
    {
        pthread_join(t[i], (void **)&result);
        res[i] = *result;
        delete result;
    }
    for (int i = 0; i < c; i++)
    {
        cout << "The result for " << i + 1 << " column is " << res[i] << endl;
    }

    for (int i = 0; i < r; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}
