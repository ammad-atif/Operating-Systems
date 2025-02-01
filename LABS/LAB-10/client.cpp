#include <cstddef>
#include <iostream>
using namespace std;
#include <sys/shm.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <fcntl.h>
int func(char *temp, int *arr)
{
  char *tok;
  tok = strtok(temp, "\n");
  int n = stoi(tok);
  int i = 0;
  while (tok != NULL)
  {
    arr[i++] = stoi(tok);
    cout << tok << endl;
    cout << arr[i - 1] << endl;
    tok = strtok(NULL, "\n");
  }
  return n;
}
int main()
{
  char *s = "number.txt";
  int fd = open(s, 0666, O_RDONLY);
  char *temp;
  int n = read(fd, temp, sizeof(temp) * 1000);
  temp[n] = '\0';
  int *arr;
  char *tok = strtok(temp, "\n");
  int sze = stoi(tok);
  sze++;
  int key = shmget(12347, 1024,
                   0);
  int *ptr = (int *)shmat(key, NULL, 0); // this call will attach the shared region to this process's address space, and return the  pointer to it. the original pointer returned is void* we can typecast it to any kind of pointer.
  cout << ptr << endl;
  int i = 0;
  while (tok != NULL)
  {
    ptr[i++] = stoi(tok);
    cout << tok << endl;
    cout << ptr[i - 1] << endl;
    tok = strtok(NULL, "\n");
  }
  // detach
  // delete []arr;
  shmdt(ptr);
  // shmctl(key, IPC_RMID, NULL); // mark the shared region for deletion
}
