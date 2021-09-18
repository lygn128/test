/*使用 mutex 和条件变量实现读写锁*/
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
using namespace std;

class MyRwLock
{
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t rmutex = PTHREAD_COND_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    int reads;

public:
    MyRwLock()
    {
    }
    MyRwLock(MyRwLock *) = delete;
    void Lock()
    {
        pthread_mutex_lock(&mutex);

        //pthread_mutex_unlock(&mutex);
        // while (reads > 0)
        // {
        //     pthread_cond_wait(&cond, &mutex);
        // }
    }

    void Ulock()
    {
        pthread_mutex_unlock(&mutex);
    }

    void RLock()
    {
        pthread_mutex_lock(&rmutex);
        reads++;
        if(read == 1) {
            pthread_mutex_lock(&mutex);
        }
        pthread_mutex_unlock(&rmutex);
    }

    void RUnlock()
    {
        pthread_mutex_lock(&rmutex);
        reads--;
        if (reads == 0)
        {
            pthread_mutex_unlock(&mutex);
            //pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&rmutex);
    }
};

int main()
{
}