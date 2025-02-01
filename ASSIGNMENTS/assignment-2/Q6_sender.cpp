#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
using namespace std;
int main()
{
    // 1 for / , 2 for * , 3 for - , 4 for +
    int msg[3];
    char op;
    int result;
    cout << "Enter operator: ";
    do
    {
        cin >> op;
        if (op != '+' && op != '-' && op != '*' && op != '/')
        {
            cout << "ENTER CORRECT OPERATOR" << endl;
        }
    } while (op != '+' && op != '-' && op != '*' && op != '/');
    switch (op)
    {
    case '/':
        msg[0] = 1;
        break;

    case '*':
        msg[0] = 2;
        break;

    case '-':
        msg[0] = 3;
        break;

    case '+':
        msg[0] = 4;
        break;
    default:
        break;
    }
    cout << "ENTER OPERAND1: " << endl;
    cin >> msg[1];
    cout << "ENTER OPERAND2: " << endl;
    cin >> msg[2];

    if (mkfifo("new_file", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            cout << "EERIR IN PIPE CREATION" << endl;
            return EXIT_FAILURE;
        }
    }
    int fd = open("new_file", O_WRONLY);
    write(fd, &msg, sizeof(int) * 3);
    close(fd);

    fd = open("new_file", O_RDONLY);
    read(fd, &result, sizeof(int));
    cout << "The result of operation is: " << result << endl;
    close(fd);
}