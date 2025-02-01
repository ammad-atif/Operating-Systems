#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <string>
using namespace std;
int f = 0;
int ptr = 0;
void *func(void *a)
{
    // int j = *(int *)a;
    int *x = (int *)a;
    while (f == 1)
        ;
    f = 1;
    // cout << "hello form " << pthread_self() << " i am created in iteration " << (j) << endl;
    cout << "hello form " << pthread_self() << " i am created in iteration " << (*x) << endl;
    fflush(stdout);
    f = 0;
    delete x;
    pthread_exit(NULL);
}
int main(int n, char *arg[])
{
    int size = stoi(arg[1]);
    pthread_t t[size];
    // int args[size];
    for (int i = 0; i < size; i++)
    {
        // args[i] = i;
        int *ptr = new int;
        *ptr = i;
        cout << "Created new thread in iteration " << i << endl;
        fflush(stdout);
        // pthread_create(&t[i], NULL, &func, (void *)&args[i]);
        pthread_create(&t[i], NULL, &func, (void *)ptr);
        if (i % 3 == 0)
        {
            sleep(1);
        }
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_join(t[i], NULL);
    }
}