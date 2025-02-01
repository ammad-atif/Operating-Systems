#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int main()
{
    int id = fork();

    if (id == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (id == 0)
    {
        cout << "PID OF CHILD FROM CHILD IS: " << getpid() << endl;
        exit(EXIT_SUCCESS);
    }
    else
    {
        int child_id = wait(NULL);
        cout << "PID OF CHILD FROM PARENT IS: " << id << endl;
        // cout << "PID OF CHILD FROM PARENT IS: " << child_id << endl;
        exit(EXIT_SUCCESS);
    }
}