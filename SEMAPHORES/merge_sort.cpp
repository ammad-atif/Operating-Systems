#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
sem_t fc1;
int factorial[10] = {0};
int count = 0;
void *fact(void *arg)
{
    int number = *(int *)arg;
    int f = 1;
    if (number <= 0)
    {
        cout << "Invalid Number" << endl;
        return 0;
    }
    else
    {
        sem_wait(&fc1);
        for (int i = 1; i <= number; i++)
        {
            f = i * f;
        }
        factorial[count] = f;
        count++;
        sem_post(&fc1);
    }
    return 0;
}

void bubbleSort()
{

    for (int i = 0; i < 10 - 1; i++)
    {
        for (int j = 0; j < 10 - i - 1; j++)
        {
            if (factorial[j] > factorial[j + 1])
            {
                swap(factorial[j], factorial[j + 1]);
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        cout << "The output of Thread number " << i << " which is factorial of " << i + 1 << " : " << factorial[i] << endl;
    }
}

int main()
{
    pthread_t threadIDs[10];
    sem_init(&fc1, 0, 1);
    int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threadIDs[i], NULL, fact, &num[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(threadIDs[i], NULL);
    }

    bubbleSort();

    sem_destroy(&fc1);

    return 0;
}
