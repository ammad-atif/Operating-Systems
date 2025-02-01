#include <chrono>;
#include <cstddef>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <thread>;
#include <unistd.h>
#define chairs 3
#define capacity 5
#define passengers 30
sem_t cables[chairs];
sem_t mutex;
using namespace std;
void *t(void *arg) {
  int i = *(int *)arg;
  int j;
  int k = 0;

  sem_wait(&mutex);
  cout << "Passenger " << i + 1 << " is waiting for chairlift" << endl;
  sem_post(&mutex);

  //
  while (1) {
    if (sem_trywait(&cables[k]) == 0) {
      j = k;
      break;
    } else {
      k = (k + 1) % chairs;
    }
  }

  sem_wait(&mutex);
  cout << "Passenger " << i + 1 << " is  on chairlift: " << j + 1 << endl;
  sem_post(&mutex);

  this_thread::sleep_for(chrono::milliseconds(500));
  //
  sem_post(&cables[j]);

  sem_wait(&mutex);
  cout << "Passenger " << i + 1 << " has left the chairlift: " << j + 1 << endl;
  sem_post(&mutex);

  delete (int *)arg;
  pthread_exit(NULL);
}
int main() {
  pthread_t people[passengers];
  sem_init(&mutex, 0, 1);
  for (int i = 0; i < chairs; i++) {
    sem_init(&cables[i], 0, capacity);
  }
  for (int i = 0; i < passengers; i++) {
    int *n = new int(i);
    pthread_create(&people[i], 0, &t, (void *)n);
  }
  for (int i = 0; i < passengers; i++) {
    pthread_join(people[i], NULL);
  }
  sem_destroy(&mutex);
  for (int i = 0; i < chairs; i++) {
    sem_destroy(&cables[i]);
  }
}