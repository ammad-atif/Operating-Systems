#include <cstddef>
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;
#define m_l 5
#define m_r 5
sem_t rope, rope2;
void *left_t(void *att) {
  int i = 0;
  while (i<m_l) {
    sem_wait(&rope);
    cout << "Monkey no " << i + 1 << " is crossing the river from left to right"
         << endl;
    fflush(stdout);
    // sleep(rand() % 3);
    cout << "Monkey no " << i + 1 << " has crossed the river from left to right"
         << endl;
    fflush(stdout);
    sem_post(&rope2);
    i++;
  }
  pthread_exit(NULL);
}
void *right_t(void *att) {
  int i = 0;
  while (i<m_r) {
    sem_wait(&rope2);
    cout << "Monkey no " << i + 1 << " is crossing the river from right to left"
         << endl;
    fflush(stdout);
    // sleep(rand() % 3);
    cout << "Monkey no " << i + 1 << " has crossed the river from right to left"
         << endl;
    fflush(stdout);
    sem_post(&rope);
    i++;
  }
  pthread_exit(NULL);
}
int main() {
  sem_init(&rope, 0, 1);
  sem_init(&rope2, 0, 0);
  pthread_t left, right;
  pthread_create(&left, NULL, left_t, NULL);
  pthread_create(&right, NULL, right_t, NULL);
  pthread_join(left, NULL);
  pthread_join(right, NULL);
  sem_destroy(&rope);
}