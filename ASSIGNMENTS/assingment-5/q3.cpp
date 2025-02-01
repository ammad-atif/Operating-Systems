#include <cstddef>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define persons 5
sem_t chopsticks[persons], mutex1, mutex2;
int even = 0;

void *table(void *att)
{
  int *i = (int *)att;
  int j = *i;
  if (j % 2 == 0)
  {
    pthread_mutex_lock(&mutex);
    cout << "Philosopher " << j << " is waiting for " << j << " and "
         << (j + 1) % persons << " chopsticks" << endl;
    pthread_mutex_unlock(&mutex);

    //
    sem_wait(&chopsticks[j]);
    sem_wait(&chopsticks[(j + 1) % persons]);

    sleep(rand() % 3);

    pthread_mutex_lock(&mutex);
    cout << "Philosopher " << j << " is having dinner with " << j << " and "
         << (j + 1) % persons << " chopsticks" << endl;
    pthread_mutex_unlock(&mutex);

    //
    sem_post(&chopsticks[(j + 1) % persons]);
    sem_post(&chopsticks[j]);

    pthread_mutex_lock(&mutex);
    cout << "Philosopher " << j << " has done dinner with " << j << " and "
         << (j + 1) % persons << " chopsticks" << endl;
    pthread_mutex_unlock(&mutex);

    sem_wait(&mutex2);
    even++;
    sem_post(&mutex2);
    if (even == 3)
    {
      sem_post(&mutex1);
    }
  }
  else
  {
    sem_wait(&mutex1);
    sem_post(&mutex1);

    pthread_mutex_lock(&mutex);
    cout << "Philosopher " << j << " is waiting for " << j << " and "
         << (j + 1) % persons << " chopsticks" << endl;
    pthread_mutex_unlock(&mutex);

    //
    sem_wait(&chopsticks[j]);
    sem_wait(&chopsticks[(j + 1) % persons]);

    sleep(rand() % 3);

    pthread_mutex_lock(&mutex);
    cout << "Philosopher " << j << " is having dinner with " << j << " and "
         << (j + 1) % persons << " chopsticks" << endl;
    pthread_mutex_unlock(&mutex);

    //
    sem_post(&chopsticks[(j + 1) % persons]);
    sem_post(&chopsticks[j]);

    pthread_mutex_lock(&mutex);
    cout << "Philosopher " << j << " has done dinner with " << j << " and "
         << (j + 1) % persons << " chopsticks" << endl;
    pthread_mutex_unlock(&mutex);
  }
  delete i;
  pthread_exit(NULL);
}
int main()
{
  pthread_t philosophers[persons];
  sem_init(&mutex1, 0, 0);
  sem_init(&mutex2, 0, 1);
  for (int i = 0; i < persons; i++)
  {
    sem_init(&chopsticks[i], 0, 1);
  }
  for (int i = 0; i < persons; i++)
  {
    int *j = new int;
    *j = i;
    pthread_create(&philosophers[i], NULL, &table, (void *)j);
  }
  for (int i = 0; i < persons; i++)
  {
    pthread_join(philosophers[i], NULL);
  }
  for (int i = 0; i < persons; i++)
  {
    sem_destroy(&chopsticks[i]);
  }
  sem_destroy(&mutex1);
  sem_destroy(&mutex2);
}
