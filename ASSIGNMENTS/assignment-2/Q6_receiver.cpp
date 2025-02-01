#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

int execute(int op, int a, int b)
{
    int result;
    switch (op)
    {
    case 1:
        result = a / b;
        break;

    case 2:
        result = a * b;
        break;

    case 3:
        result = a - b;
        break;

    case 4:
        result = a + b;
        break;

    default:
        break;
    }
    return result;
}
int main()
{
    int msg[3];
    int res;

    int fd = open("new_file", O_RDONLY);
    read(fd, msg, sizeof(int) * 3);
    res = execute(msg[0], msg[1], msg[2]);
    close(fd);

    fd = open("new_file", O_WRONLY);
    write(fd, &res, sizeof(int));
    close(fd);
}