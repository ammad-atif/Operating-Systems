#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

sem_t semaphore_a;
sem_t semaphore_c;
sem_t semaphore_b;

int total = 0;
void *a_print(void *arg)
{
    int a = 0;
    while (total < 10)
    {
        sem_wait(&semaphore_a);
        if (total < 10)
        {
            for (int i = 0; i < 3; i++)
            {
                cout << "a";
                /* code */
            }
        }
        sem_post(&semaphore_c);
    }
    return 0;
}

void *b_print(void *arg)
{
    while (total < 10)
    {
        sem_wait(&semaphore_b);
        cout << "b";
        total++;
        sem_post(&semaphore_a);
    }
    return 0;
}

void *c_print(void *arg)
{
    while (total < 10)
    {
        sem_wait(&semaphore_c);
        if (total < 10)
        {
            cout << "c";
        }
        sem_post(&semaphore_b);
    }
    return 0;
}

int main()
{
    pthread_t threadIDs[3];

    sem_init(&semaphore_a, 0, 1);
    sem_init(&semaphore_c, 0, 0);
    sem_init(&semaphore_b, 0, 0);

    pthread_create(&threadIDs[0], NULL, a_print, NULL);
    pthread_create(&threadIDs[1], NULL, b_print, NULL);
    pthread_create(&threadIDs[2], NULL, c_print, NULL);

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threadIDs[i], NULL);
    }

    sem_destroy(&semaphore_a);
    sem_destroy(&semaphore_c);
    sem_destroy(&semaphore_b);

    return 0;
}
