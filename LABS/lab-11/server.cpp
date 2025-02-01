#include <iostream>
#include <sys/shm.h>
#include <unistd.h>
using namespace std;

class Student {
public:
  int rollNumber;
  char name[20];
};

int main() {

  int key = shmget(11223, 1024,
                   IPC_CREAT | IPC_EXCL |
                       0666); // 12321 is the user key// 1024 is the bytes we
                              // want to use as shared memory

  char *ptr = (char *)shmat(
      key, NULL,
      0); // this call will attach the shared region to this process's address
          // space, and return the  pointer to it. the original pointer returned
          // is void* we can typecast it to any kind of pointer.

  cout << "shm created with id= " << key << endl;
  ptr[0] = -1;

  cout << "Waiting for the client process to send data.!" << endl;
  while (ptr[0] == -1)
    ; // busy wait
  usleep(2000);
  cout << endl;

  for (int i = 0; i <= ptr[0]; i++) {
    if (i == 0) {
      cout << "counter: " << ptr[0] << endl;
    } else {
      cout << ptr[i];
    }
  }
  cout << endl;
  // detach
  usleep(2000);
  shmdt(ptr);

  shmctl(key, IPC_RMID, NULL); // mark the shared region for deletion
}
