#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
sem_t semaphore1;
sem_t semaphore2;
int Counter = 0;
void *increment_1(void *args)
{
  while (Counter < 200)
  {
    sem_wait(&semaphore1);
    if (Counter < 200)
    {
      cout << "increment 1: " << Counter << endl;
      Counter++;
    }
    sem_post(&semaphore2);
  }

  return 0;
}

void *increment_2(void *args)
{
  while (Counter < 200)
  {
    sem_wait(&semaphore2);

    cout << "increment 2: " << Counter << endl;
    Counter++;
    sem_post(&semaphore1);
  }

  return 0;
}

int main()
{
  pthread_t threadIDs[2];

  sem_init(&semaphore1, 0, 1);
  sem_init(&semaphore2, 0, 0);

  pthread_create(&threadIDs[0], NULL, increment_1, NULL);
  pthread_create(&threadIDs[1], NULL, increment_2, NULL);

  for (int i = 0; i < 2; i++)
  {
    pthread_join(threadIDs[i], NULL);
  }

  sem_destroy(&semaphore1);
  sem_destroy(&semaphore2);

  return 0;
}
