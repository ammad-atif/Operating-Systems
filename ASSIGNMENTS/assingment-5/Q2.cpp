#include <cstddef>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define students_allowed 10
sem_t total_space, o_cpu;

void *student_func(void *arg)
{
    while (1)
    {
        int x;
        sem_getvalue(&total_space, &x);
        if (x == 0)
        {
            pthread_mutex_lock(&mutex);
            cout << "Student is waiting" << endl;
            pthread_mutex_unlock(&mutex);
        }
        //
        sem_wait(&total_space);

        pthread_mutex_lock(&mutex);
        cout << "Student enters the lab" << endl;
        pthread_mutex_unlock(&mutex);

        //
        sem_post(&o_cpu);
    }
    pthread_exit(0);
}

void *lab_func(void *arg)
{
    int *i = (int *)arg;
    int j = *i;
    while (1)
    {
        //
        sem_wait(&o_cpu);

        pthread_mutex_lock(&mutex);
        cout << "Student is working on computer no: " << j + 1 << endl;
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 5);

        pthread_mutex_lock(&mutex);
        cout << "Student left the computer no: " << j + 1 << endl;
        pthread_mutex_unlock(&mutex);

        //
        sem_post(&total_space);
    }
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    pthread_t student, lab[10];
    int x[students_allowed];
    sem_init(&total_space, 0, students_allowed);
    sem_init(&o_cpu, 0, 0);
    pthread_create(&student, NULL, student_func, NULL);
    for (int i = 0; i < students_allowed; i++)
    {
        x[i] = i;
        pthread_create(&lab[i], NULL, lab_func, (void *)&x[i]);
    }
    pthread_join(student, NULL);
    for (int i = 0; i < students_allowed; i++)
    {
        pthread_join(lab[i], NULL);
    }
    sem_destroy(&total_space);
    sem_destroy(&o_cpu);
    return 0;
}
