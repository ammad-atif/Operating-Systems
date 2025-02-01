#include <cstddef>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <string>

using namespace std;
void *func(void *a)
{
    char *arr = (char *)a;
    int *x = new int(0);
    char *tok;
    tok = strtok(arr, " \0");
    while (tok != NULL)
    {
        *x = *x + stoi(tok);
        tok = strtok(NULL, " \0");
    }

    pthread_exit((void *)x);
};

typedef void *(*holder)(void *);

int main()
{
    int fd = open("file.txt", O_RDONLY);
    char a[1000];
    int n = read(fd, a, sizeof(char) * 1000);
    a[n] = '\0';
    // cout << a << endl;
    int rows = 0;
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] == '\n')
        {
            rows++;
        }
    }
    rows++;
    // cout << rows << endl;
    pthread_t t[rows];

    char *arr[rows];
    int sum[rows];
    char *tok;
    tok = strtok(a, "\n\0");
    int j = 0;
    while (tok != NULL)
    {
        // cout << tok << endl;
        arr[j++] = tok;
        tok = strtok(NULL, "\n\0");
    }

    for (int i = 0; i < rows; i++)
    {
        pthread_create(&t[i], NULL, &func, (void *)arr[i]);
    }
    for (int i = 0; i < rows; i++)
    {
        int *temp;
        pthread_join(t[i], (void **)&temp);
        sum[i] = *temp;
        cout << "sum of : " << arr[i] << endl;
        cout << sum[i] << endl;
        delete temp;
    }

    close(fd);
}