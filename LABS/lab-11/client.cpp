#include <cstddef>
#include <iostream>
using namespace std;
#include <cstring>
#include <fcntl.h>
#include <stdio.h>
#include <string>
#include <sys/shm.h>
#include <unistd.h>
int func(char *temp, int *arr) {
  char *tok;
  tok = strtok(temp, "\n");
  int n = stoi(tok);
  int i = 0;
  while (tok != NULL) {
    arr[i++] = stoi(tok);
    cout << tok << endl;
    cout << arr[i - 1] << endl;
    tok = strtok(NULL, "\n");
  }
  return n;
}
int main() {
  char message[256];
  cout << "Enter message" << endl;
  cin >> message;
  int n = strlen(message);
  int key = shmget(11223, 1024, 0);
  char *ptr = (char *)shmat(
      key, NULL,
      0); // this call will attach the shared region to this process's address
          // space, and return the  pointer to it. the original pointer returned
          // is void* we can typecast it to any kind of pointer.
  cout << ptr << endl;
  int i = 0;

  char temp[100];
  sprintf(temp, "%d", n);
  char *temp2 = strdup(temp);
  ptr[i] = *temp2;
  delete temp2;
  i++;
  while (i < n + 1) {
    ptr[i] = message[i - 1];
    i++;
  }
  // detach
  // delete []arr;
  shmdt(ptr);
  // shmctl(key, IPC_RMID, NULL); // mark the shared region for deletion
}
