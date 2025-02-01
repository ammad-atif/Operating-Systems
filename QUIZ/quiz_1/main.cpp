#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <cstdio>
using namespace std;

int main(int s, char *args[])
{
  int fd[2];
  pipe(fd);
  srand(time(NULL));

  int m = stoi(args[1]);
  int n = stoi(args[2]);

  int pid = fork();

  if (pid < 0)
  {
    exit(EXIT_FAILURE);
  }
  else if (pid == 0)
  {
    close(fd[0]);
    int arr[m][n];
    cout << "FROM MAIN PROCESS" << endl;
    for (int i = 0; i < m; i++)
    {
      cout << "THE NUMBERS GENERATED ARE" << endl;
      for (int j = 0; j < n; j++)
      {
        arr[i][j] = (rand() % 101);
        cout << arr[i][j] << " ";
      }
      cout << endl;
      write(fd[1], arr[i], sizeof(int) * n);
      kill(getpid(), SIGSTOP);
    }
    close(fd[1]);
  }
  else
  {
    int exitstatus = 0;
    int read_arr[n];
    int even_num[n * m];
    int j = 0;
    close(fd[1]);
    for (int k = 0; k < m; k++)
    {
      read(fd[0], read_arr, sizeof(int) * n);
      cout << "EVEN NUMBERS ARE:" << endl;
      for (int i = 0; i < n; i++)
      {
        if (read_arr[i] % 2 == 0)
        {
          even_num[j] = read_arr[i];
          cout << even_num[j] << " ";
          j++;
        }
      }
      cout << endl;
      kill(pid, SIGCONT);
    }
    close(fd[0]);
    wait(NULL);

    char *arr[j + 3];

    arr[0] = "./array";

    arr[j + 2] = NULL;

    char xyz[100];

    sprintf(xyz, "%d", j);
    arr[1] =strdup(xyz);

    for (int i = 0; i < j; i++)
    {
      sprintf(xyz, "%d", even_num[i]);
      arr[i + 2] = strdup(xyz);
      cout << arr[i + 2] << endl;
    }
    if (execvp("./array", arr) == -1)
    {
      perror("execvp failed");
      exit(EXIT_FAILURE);
    }
  }
}