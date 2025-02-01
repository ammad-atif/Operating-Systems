#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
int forks[5] = {1, 2, 3, 4, 5};
int professors[5] = {1, 2, 3, 4, 5};
int evencount = 0;
int oddcount = 0;
int f1, f2 = 0;
sem_t semaphore_a;
sem_t semaphore_b;
void *dining(void *args)
{
    int professor_number = *(int *)args;
    if (professor_number % 2 == 0)
    {
        sem_wait(&semaphore_a);
        evencount++;
        f1 = forks[professor_number - 1];
        f2 = forks[(professor_number) % 5];
        cout << "The philosopher number " << professor_number << " is eating with fork numbers: " << f1 << " " << f2 << endl;
        sem_post(&semaphore_a);
        sleep(2);
        if (evencount == 2)
        {
            sem_post(&semaphore_b);
        }
    }
    else
    {
        sem_wait(&semaphore_b);
        f1 = forks[professor_number - 1];
        f2 = forks[(professor_number) % 5];
        cout << "The philosopher number " << professor_number << " is eating with fork numbers: " << f1 << " " << f2 << endl;
        sem_post(&semaphore_b);
    }

    return 0;
}
int main()
{
    pthread_t threadIDs[5];
    sem_init(&semaphore_a, 0, 1);
    sem_init(&semaphore_b, 0, 0);

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&threadIDs[i], NULL, dining, &professors[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threadIDs[i], NULL);
    }

    sem_destroy(&semaphore_a);
    sem_destroy(&semaphore_b);

    return 0;
}
