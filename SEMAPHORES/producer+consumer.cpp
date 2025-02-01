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

char output_buffer[100];

void *producer(void *arg)
{
    while (count < 100)
    {

        sem_wait(&semaphore_p);
        if (count < 100)
        {
            buffer = count;
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
        sprintf(output_buffer, "The consumer at this point is: %d\n", buffer);
        puts(output_buffer);
        count++;
        sem_post(&semaphore_p);
    }
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
