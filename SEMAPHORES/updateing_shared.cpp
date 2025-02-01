#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
sem_t semaphore_A;
sem_t semaphore_B;
sem_t semaphore_C;
int i = 0;

int sharedaccount = 1000;
void *update_A(void *args)
{
    while (i < 5)
    {
        sem_wait(&semaphore_A);
        if (i < 5)
        {
            sharedaccount = sharedaccount - 200;
            cout << "Thread A has updated Data: " << i + 1 << " times " << endl;
            cout << "Value now is: " << sharedaccount << endl;
        }
        sem_post(&semaphore_B);
    }
    return 0;
}

void *update_B(void *args)
{
    while (i < 5)
    {
        sem_wait(&semaphore_B);
        if (i < 5)
        {
            sharedaccount = sharedaccount - 200;
            cout << "Thread B has updated Data: " << i + 1 << " times " << endl;
            cout << "Value now is: " << sharedaccount << endl;
        }
        sem_post(&semaphore_C);
    }
    return 0;
}

void *update_C(void *args)
{
    while (i < 5)
    {
        sem_wait(&semaphore_C);
        sharedaccount = sharedaccount - 200;
        cout << "Thread C has updated Data: " << i + 1 << " times " << endl;
        cout << "Value now is: " << sharedaccount << endl;
        i++;
        sem_post(&semaphore_A);
    }
    return 0;
}

int main()
{
    pthread_t threadIDs[3];

    sem_init(&semaphore_A, 0, 1);
    sem_init(&semaphore_B, 0, 0);
    sem_init(&semaphore_C, 0, 0);

    pthread_create(&threadIDs[0], NULL, update_A, NULL);
    pthread_create(&threadIDs[1], NULL, update_B, NULL);
    pthread_create(&threadIDs[2], NULL, update_C, NULL);

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threadIDs[i], NULL);
    }

    sem_destroy(&semaphore_A);
    sem_destroy(&semaphore_B);
    sem_destroy(&semaphore_C);

    return 0;
}
