#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
using namespace std;

int main()
{
    int pipe_1[2];
    int pipe_2[2];
    if (pipe(pipe_1) == -1 || pipe(pipe_2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int id = fork();

    if (id == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (id == 0)
    {
        close(pipe_1[1]);
        close(pipe_2[0]);

        int sum = 0;
        int temp;
        int n;
        read(pipe_1[0], &n, sizeof(int));
        for (int i = 0; i < n; i++)
        {
            read(pipe_1[0], &temp, sizeof(int));
            sum = sum + temp;
        }
        write(pipe_2[1], &sum, sizeof(int));

        close(pipe_1[0]);
        close(pipe_2[1]);
    }
    else
    {
        close(pipe_1[0]);
        close(pipe_2[1]);

        int sum;
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int n = sizeof(arr) / sizeof(arr[0]);
        write(pipe_1[1], &n, sizeof(int));
        write(pipe_1[1], arr, sizeof(int) * n);
        read(pipe_2[0], &sum, sizeof(int));
        cout << "THE SUM IS: " << sum << endl;

        close(pipe_1[1]);
        close(pipe_2[0]);
    }
}
