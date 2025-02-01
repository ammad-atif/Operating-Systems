#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int start, end, sum = 0;
    int fd[2];
    if (pipe(fd) == -1)
    {
        cout << "ERROR OCCURED" << endl;
        exit(0);
    }

    int pid = fork();

    if (pid < 0)
    {
        cout << "ERROR OCCURED" << endl;
        exit(0);
    }
    else if (pid == 0)
    {
        start = 0;
        end = n / 2;
    }
    else
    {
        start = n / 2;
        end = n;
    }

    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }

    if (pid == 0)
    {
        close(fd[0]);
        cout << "sum of child is: " << sum << endl;
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        cout << "sum of parent is: " << sum << endl;
        int new_sum = 0;
        read(fd[0], &new_sum, sizeof(int));
        close(fd[0]);
        cout << "new sum is: " << sum + new_sum << endl;
    }
}