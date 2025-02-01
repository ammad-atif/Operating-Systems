#include <cstddef>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;
#define max_rooms 3
#define room_capacity 4
int max_students;
sem_t av_rooms[max_rooms];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *studentFunction(void *id)
{
    int *x = (int *)id;
    int studentID = *((int *)id);
    studentID++;

    pthread_mutex_lock(&mutex);
    cout << "Student " << studentID << " is trying to enter the library." << endl;
    pthread_mutex_unlock(&mutex);

    //
    int roomIndex = -1;
    int i = 0;
    while (i < max_rooms)
    {
        if (sem_trywait(&av_rooms[i]) == 0)
        {
            roomIndex = i;
            break;
        }
        i = i + 1;
        i = i % max_rooms;
    }

    pthread_mutex_lock(&mutex);
    cout << "Student " << studentID << " enters the library and occupies study room " << roomIndex + 1 << "." << endl;
    pthread_mutex_unlock(&mutex);

    sleep(rand() % 3);

    pthread_mutex_lock(&mutex);
    cout << "Student " << studentID << " leaves study room " << roomIndex + 1 << "." << endl;
    pthread_mutex_unlock(&mutex);

    //
    sem_post(&av_rooms[roomIndex]);

    delete x;
    pthread_exit(NULL);
}
void *inc_func(void *arg)
{
    while (1)
    {
        max_students++;
        sleep(1);
    }
    pthread_exit(NULL);
}
int main()
{

    pthread_t students[10000], inc;

    for (int i = 0; i < max_rooms; ++i)
    {
        sem_init(&av_rooms[i], 0, room_capacity);
    }

    pthread_create(&inc, NULL, inc_func, NULL);
    int i = 0;
    int j = 0;
    while (1)
    {
        for (; i < max_students; ++i)
        {
            int *x = new int(i);
            pthread_create(&students[i], NULL, studentFunction, (void *)x);
        }

        for (; j < max_students; ++j)
        {
            pthread_join(students[j], NULL);
        }
        // sleep(3);
    }
    for (int k = 0; k < max_rooms; ++k)
    {
        sem_destroy(&av_rooms[k]);
    }
    pthread_join(inc, NULL);
    return 0;
}
