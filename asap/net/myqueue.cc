#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <queue>
using namespace std;

void P(pthread_mutex_t *lock)
{
    pthread_mutex_lock(lock);
}

void V(pthread_mutex_t *lock)
{
    pthread_mutex_unlock(lock);
}

template<class T>
class MyQueue
{
    std::queue<T> qu;
    int capacity;
    pthread_mutex_t mutex;
    pthread_cond_t cond_full, cond_empty;

public:
    MyQueue(int size) : capacity(size)
    {
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&cond_full, NULL);
        pthread_cond_init(&cond_empty, NULL);
    }
    void put(T t)
    {
        P(&this->mutex);
        if (this->qu.size() > this->capacity)
        {
            pthread_cond_wait(&cond_full, &this->mutex);
            qu.push(t);
        }
        V(&this->mutex);
        pthread_cond_signal(&cond_empty);
    }

    T get()
    {
        P(&this->mutex);
        if (this->qu.size() == 0)
        {
            //pthread_cond_wait(&mutex, &cond_full);
            pthread_cond_wait(&cond_empty, &this->mutex);
        }
        T t = qu.front();
        qu.pop();
        V(&this->mutex);
        pthread_cond_signal(&cond_full);
        return t;
    }
};



void *loop_put(void * arg) {
    MyQueue<int> *qu = (MyQueue<int> *)arg;
    int i = 0;
    while(1) {
        sleep(1);
        qu->put(i++);
    }

}

void *loop_get(void * arg) {
    MyQueue<int> *qu = (MyQueue<int> *)arg;
    //int i = 0;
    while(1) {
        qu->get();
    }

}

int main()
{
    MyQueue<int> qu(2);
    pthread_t tid1, tid2, tid3, tid4;
    pthread_create(&tid1, NULL, loop_get, &qu);
    pthread_create(&tid2, NULL, loop_get, &qu);
    pthread_create(&tid3, NULL, loop_put, &qu);
    pthread_create(&tid4, NULL, loop_put, &qu);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
}