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
    char msg[100];
    cin.getline(msg, 100);
    int n = strlen(msg);
    ++n;
    if (mkfifo("file", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            cout << "EERIR IN PIPE CREATION" << endl;
            return EXIT_FAILURE;
        }
    }
    int fd = open("file", O_WRONLY);
    write(fd, &n, sizeof(int));
    write(fd, &msg, sizeof(char) * n);
    close(fd);

    fd = open("file", O_RDONLY);
    read(fd, &n, sizeof(int));
    read(fd, msg, sizeof(char) * n);
    cout << msg << endl;
    close(fd);
}