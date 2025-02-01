#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <iostream>
using namespace std;

int buffer = 0;
sem_t semaphore_p;
sem_t semaphore_c;
int sum = 0;
int count = 0;
int arr[100];
int i = 0;
void *producer(void *arg)
{
    while (count < 100)
    {
        sem_wait(&semaphore_p);
        if (count < 100)
        {
            buffer = (rand() % 6) + 1;
            arr[i] = buffer;
            i++;
            cout << "producer  : " << count << endl;
            cout << "producer produces : " << buffer << endl;
        }
        sem_post(&semaphore_c);
    }
    return 0;
}

void *consumer(void *arg)
{
    while (count < 100)
    {
        sem_wait(&semaphore_c);
        sum += arr[i - 1];
        cout << "consumer  : " << count << endl;
        cout << "consumer consumed : " << arr[i - 1] << endl;
        i--;
        count++;
        sem_post(&semaphore_p);
    }
    cout << "SUM: " << sum << endl;
    return 0;
}

int main()
{
    pthread_t threadIDs[2];

    sem_init(&semaphore_p, 0, 1);
    sem_init(&semaphore_c, 0, 0);

    pthread_create(&threadIDs[0], NULL, producer, NULL);
    pthread_create(&threadIDs[1], NULL, consumer, NULL);

    pthread_join(threadIDs[0], NULL);
    pthread_join(threadIDs[1], NULL);

    sem_destroy(&semaphore_p);
    sem_destroy(&semaphore_c);

    return 0;
}
