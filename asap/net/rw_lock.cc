#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

void P(sem_t *sem)
{
    sem_wait(sem);
}

void V(sem_t *sem)
{
    sem_post(sem);
}
class RWLocker
{
public:
    sem mutext;
    sem w_sem;
    int read_count;
    RWLocker() = delete;
    RWLocker(int max_Read)
    {
        sem_init(&mutext, 0, 1);
        sem_init(&w_sem, 0, 1);
    }
    void lock()
    {
        P(&w_sem);
    }
    void ulock()
    {
        V(&w_sem);
    }

    void rlock()
    {
        P(&this->mutext);
        read_count++;
        if(read_count == 1) P(&this->w_sem);
        V(&this->mutext);

    }

    void rulock()
    {
        P(&this->mutext);
        read_count--;
        if(read_count == 0) {
            V(&this->w_sem);
        }
        V(&this->mutext);
    }
};