#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
using namespace std;
int main()
{
    int get = 0;
    int sum = 0;
    int fd = open("myfifo", O_RDONLY);
    cout << "opening receive" << endl;
    do
    {
        if (read(fd, &get, sizeof(int)) == -1)
        {
            cout << "not read" << endl;
            return EXIT_FAILURE;
        }
        cout << "read" << endl;
        sum += get;
        cout << "SUM IS: " << sum << endl;
    } while (get != -99);
    close(fd);
}