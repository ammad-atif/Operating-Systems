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
    int input = 0;
    if (mkfifo("myfifo", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            cout << "EERIR IN PIPE CREATION" << endl;
            return EXIT_FAILURE;
        }
    }
    int fd = open("myfifo", O_WRONLY);
    cout << "opening" << endl;
    do
    {
        cout << "Enter number" << endl;
        cin >> input;
        if (write(fd, &input, sizeof(int)) == -1)
        {
            cout << "not written" << endl;
            return EXIT_FAILURE;
        }
         cout << "written" << endl;
    } while (input != -99);
    close(fd);
}