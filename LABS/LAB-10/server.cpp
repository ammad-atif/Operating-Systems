#include <iostream>
#include <string>
#include <sys/shm.h>
#include <unistd.h>
using namespace std;

class Student
{
public:
  int rollNumber;
  char name[20];
};

int main()
{

  int key = shmget(12347, 1024,
                   IPC_CREAT | IPC_EXCL |
                       0666); // 12321 is the user key// 1024 is the bytes we
                              // want to use as shared memory

  int *ptr = (int *)shmat(
      key, NULL,
      0); // this call will attach the shared region to this process's address
          // space, and return the  pointer to it. the original pointer returned
          // is void* we can typecast it to any kind of pointer.

  cout << "shm created with id= " << key << endl;
  ptr[0] = -1;

  cout << "Waiting for the client process to send data.!" << endl;
  while (ptr[0] == -1)
    ; // busy wait
  usleep(1000);
  cout << endl;
  int sum = 0;
  for (int i = 1; i <= ptr[0]; i++)
  {
    cout<<ptr[i]<<endl;
    sum += ptr[i];
  }
  cout << "sum: " << sum << endl;
  cout << "average: " << sum / ptr[0] << endl;
  // detach
  shmdt(ptr);

  shmctl(key, IPC_RMID, NULL); // mark the shared region for deletion
}
