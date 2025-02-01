#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

sem_t semaphore_a;
sem_t semaphore_c;
sem_t semaphore_b;
int a = 0;
int i_a = 0;
int j_a = 0;
int k_a = 0;
void *a_print(void *arg)
{
    while (i_a < 30)
    {
        i_a++;
        cout << "a";
        a = a + 1;
        if (a == 3)
        {
            sem_post(&semaphore_c);
            sem_wait(&semaphore_a);
            a = 0;
        }
    }
    return 0;
}

void *b_print(void *arg)
{
    while (j_a < 10)
    {
        j_a++;
        sem_wait(&semaphore_b);
        cout << "b";
        sem_post(&semaphore_a);
    }
    return 0;
}

void *c_print(void *arg)
{
    while (k_a < 10)
    {
        k_a++;
        sem_wait(&semaphore_c);
        cout << "c";
        sem_post(&semaphore_b);
    }
    return 0;
}

int main()
{
    pthread_t threadIDs[3];

    sem_init(&semaphore_a, 0, 0);
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
