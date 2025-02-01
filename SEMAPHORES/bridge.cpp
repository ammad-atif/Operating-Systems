#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;
sem_t semaphore1;
sem_t semaphore2;
int Counter = 0;
int turn = 0;
void *bridge_1_side(void *args)
{
    while (Counter < 2)
    {
        cout << "VEHCILE 1 WAITING" << endl;
        sem_wait(&semaphore1);
        cout << "VEHCILE 1 TURN" << endl;
        cout << "VEHCILE 1 EXIT" << endl;
        sem_post(&semaphore2);
    }

    return 0;
}

void *bridge_2_side(void *args)
{
    while (Counter < 2)
    {
        cout << "VEHCILE 2 WAITING" << endl;
        sem_wait(&semaphore2);
        cout << "VEHCILE 2 TURN" << endl;
        Counter++;
        cout << "VEHCILE 2 EXIT" << endl;
        sem_post(&semaphore1);
    }

    return 0;
}

int main()
{
    pthread_t threadIDs[2];

    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 0);

    pthread_create(&threadIDs[0], NULL, bridge_1_side, NULL);
    pthread_create(&threadIDs[1], NULL, bridge_2_side, NULL);

    for (int i = 0; i < 2; i++)
    {
        pthread_join(threadIDs[i], NULL);
    }

    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);

    return 0;
}
