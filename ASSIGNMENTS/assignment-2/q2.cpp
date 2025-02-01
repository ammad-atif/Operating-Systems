#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
using namespace std;
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
        close(fd[0]);
        // 1 for deposit //2 for withdrawl //4 for exit
        int arr[3];
        do
        {
            do
            {
                cout << "enter 1 to deposit" << endl;
                cout << "enter 2 to withdraw" << endl;
                cout << "enter 3 to display balance" << endl;
                cout << "enter 4 to exit" << endl;
                cin >> arr[0];
            } while (arr[0] != 1 && arr[0] != 2 && arr[0] != 3 && arr[0] != 4);

            if (arr[0] != 4 && arr[0] != 3)
            {
                cout << "ENTER AMOUNT: " << endl;
                cin >> arr[1];
                cout << "Enter account number from 1 to 10 you want to access: " << endl;
                cin >> arr[2];
                write(fd[1], arr, sizeof(int) * 3);
            }
            else if (arr[0] == 3)
            {
                cout << "Enter account number from 1 to 10 you want to access: " << endl;
                cin >> arr[1];
                write(fd[1], arr, sizeof(int) * 2);
            }
            else
            {
                write(fd[1], &arr[0], sizeof(int) * 1);
            }
            kill(getpid(), SIGSTOP);
        } while (arr[0] != 4);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int amount[10] = {0};
        int temp_amount;
        int check = 0;
        int x = 0;
        // wait(NULL);
        do
        {
            read(fd[0], &check, sizeof(int));
            if (check != 4)
            {
                if (check == 3)
                {
                    read(fd[0], &x, sizeof(int));
                    if (x > 0 && x < 11)
                    {
                        cout << "TOTAL BALANCE: " << amount[x - 1] << endl;
                    }
                    else
                    {
                        cout << "WRONG ACCOUNT NUMBER" << endl;
                    }
                }
                else
                {

                    read(fd[0], &temp_amount, sizeof(int));
                    read(fd[0], &x, sizeof(int));
                    if (x > 0 && x < 11)
                    {
                        if (check == 1)
                        {
                            cout << "DEPOSIT SUCCESSFULL" << endl;
                            amount[x - 1] += temp_amount;
                            cout << "THE TOTAL AMOUNT NOW IS: " << amount[x - 1] << endl;
                        }
                        else if (check == 2)
                        {
                            if ((amount[x - 1] - temp_amount) < 0)
                            {
                                cout << "WITHDRAW UNSUCCESSFULL" << endl;
                            }
                            else
                            {
                                amount[x - 1] = amount[x - 1] - temp_amount;
                                cout << "WITHDRAW SUCCESSFULL" << endl;
                                cout << "THE TOTAL AMOUNT NOW IS: " << amount[x - 1] << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "WRONG ACCOUNT NUMBER" << endl;
                    }
                }
            }
            kill(id, SIGCONT);
        } while (check != 4);
        close(fd[0]);
    }
}