#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
#define MAX_CHAIRS 5 // Maximum number of chairs in the waiting room
int num_waiting = 0; // Number of customers currently present in barber shop
int customer_sem = 0;
int mutex = 1;

void wait(int *x)
{
    if (*x <= 0)
    {
        cout << "Barber is sleeping\n";
        while (*x == 0)
            ;
    }
    pthread_mutex_lock(&m);
    (*x)--;
    pthread_mutex_unlock(&m);
}

void post(int *x)
{
    pthread_mutex_lock(&m);
    (*x)++;
    pthread_mutex_unlock(&m);
}

void *barber(void *arg)
{
    while (1)
    {
        wait(&customer_sem);

        cout << "Barber is cutting hair\n";
        sleep(1); // hair cutting
        cout << "Hair cut is completed\n";

        wait(&mutex);
        num_waiting--;
        post(&mutex);
    }
}

void *customer(void *arg)
{
    while (1)
    {
        wait(&mutex);
        if (num_waiting < MAX_CHAIRS)
        {
            num_waiting++;
            post(&mutex);

            cout << "Customer got seated\n";
            post(&customer_sem);
        }
        else
        {
            post(&mutex);
            cout << "No free chairs, customer leaves\n";
        }
        usleep(500000);
    }
}

int main()
{
    pthread_t barber_thread, customer_thread;

    pthread_create(&barber_thread, NULL, barber, NULL);
    pthread_create(&customer_thread, NULL, customer, NULL);

    pthread_join(barber_thread, NULL);
    pthread_join(customer_thread, NULL);

    return 0;
}
