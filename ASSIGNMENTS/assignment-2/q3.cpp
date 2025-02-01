#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
using namespace std;

bool isPrime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    if (num <= 3)
    {
        return true;
    }
    else
    {
        for (int i = 2; i <= num / 2; ++i)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }
}

int main()
{
    int fd[2];
    if (pipe(fd) == -1)
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
        close(fd[1]);
        int range;
        read(fd[0], &range, sizeof(int));
        close(fd[0]);
        for (int i = 0; i < range; i++)
        {
            if (isPrime(i))
            {
                cout << i << endl;
            }
        }
    }
    else
    {
        close(fd[0]);
        srand(time(NULL));
        int random = rand();
        random=(random% 100) + 1;
        cout<<"RANGE:"<<random<<endl;
        write(fd[1], &random, sizeof(int));
        close(fd[1]);
    }
}
