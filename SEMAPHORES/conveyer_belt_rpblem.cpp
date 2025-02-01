#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <semaphore.h>

#define BELT_CAPACITY 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 2
int producer_i[NUM_PRODUCERS] = {0};
int consumer_i[NUM_CONSUMERS] = {0};

int x = 0;
int y = 0;
int belt[5] = {0};
sem_t a;
sem_t b;
int i = 0;
void *produce(void *arg)
{
    int producer_id = *((int *)(&arg));
    while (producer_i[producer_id] < 4)
    {
        sem_wait(&a);
        x = producer_id;
        int item = rand() % 100 + 1; // Produce a random item
        belt[i++] = item;
        std::cout << "Producer " << producer_id << " produced item " << item << ".\n";
        ++producer_i[producer_id];
        sem_post(&b);
    }
    return NULL;
}

void *consume(void *arg)
{
    int consumer_id = *((int *)(&arg));
    while (consumer_i[consumer_id] < 6)
    {
        sem_wait(&b);
        y = consumer_id;
        i--;
        int item = belt[i];
        std::cout << "Consumer " << consumer_id << " consumed item " << item << ".\n";
        ++consumer_i[consumer_id];
        sem_post(&a);
    }
    return NULL;
}

int main()
{
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    sem_init(&a, 0, 1);
    sem_init(&b, 0, 0);

    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        producer_i[i] = 0;
    }

    // Initialize consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        consumer_i[i] = 0;
    }

    // Initialize producer threads
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        producer_ids[i] = i;
        pthread_create(&producer_threads[i], NULL, produce, (void *)producer_ids[i]);
    }

    // Initialize consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        consumer_ids[i] = i;
        pthread_create(&consumer_threads[i], NULL, consume, (void *)consumer_ids[i]);
    }

    // Join producer threads
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        pthread_join(producer_threads[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&a);
    sem_destroy(&b);
    return 0;
}
