#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

void shiftCase(char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 'a' + 'A';
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}
int main()
{
    char msg[100];
    int n;
    int fd = open("file", O_RDONLY);
    read(fd, &n, sizeof(int));
    read(fd, msg, sizeof(char) * n);
    cout << msg<<endl;
    shiftCase(msg);
    close(fd);


    fd = open("file", O_WRONLY);
    write(fd, &n, sizeof(int));
    write(fd, &msg, sizeof(char) * n);
    close(fd);

}