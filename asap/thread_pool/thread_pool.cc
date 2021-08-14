#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <atomic>
#include <sys/types.h>
#include <sys/syscall.h>
#include <semaphore.h>
using namespace std;
#define gettid() syscall(SYS_gettid)

class Thread_pool;
class Task
{
public:
    void (*func)(void *args);
    void *arg;

    Task()
    {
    }
    void run()
    {
        func(arg);
    }
};

void *xrun(void *arg);

void P(sem_t *se)
{
    sem_wait(se);
}

void V(sem_t *se)
{
    sem_post(se);
}

class Thread_pool
{
    int thread_num;
    std::queue<Task *> qu;
    sem_t mutext;
    sem_t slots;
    sem_t items;
    pthread_t *threads;
    std::atomic<bool> running;

public:
    Thread_pool(int num)
    {
        this->thread_num = num;
        threads = new pthread_t(num);
        sem_init(&mutext, 0, 1);
        sem_init(&slots, 0, 100);
        sem_init(&items, 0, 0);
    }

    void Submit_task(Task *task)
    {
        P(&slots);
        P(&mutext);
        qu.push(task);
        V(&mutext);
        //V(&slots);
        V(&items);
    }

    void run()
    {
        static std::atomic_int x(0);
        x++;
        while (1)
        {
            P(&items);
            P(&mutext);
            Task *task = qu.front();
            qu.pop();
            V(&mutext);
            //V(&items);
            V(&slots);
            task->run();
            //std::cout << "thread is:" << gettid() << std::endl;
            //sleep(1);
        }
    }

    void start()
    {
        if (!running.load())
        {
            running.store(true);
            for (int i = 0; i < this->thread_num; i++)
            {
                pthread_create(&threads[i], NULL, xrun, this);
            }
        }else {

        }
    }

    void stop()
    {
        for (int i = 0; i < this->thread_num; i++)
        {
            pthread_join(threads[i], NULL);
        }
        delete threads;
    }
    Thread_pool() = delete;
};

void *xrun(void *arg)
{
    Thread_pool *pool = static_cast<Thread_pool *>(arg);
    pool->run();
}

void test(void *xx)
{
    int *a = (int *)xx;
    //std::cout << "val is:" << *a << std::endl;
    printf("val is  thread is %d  %d\n", gettid(), *a);
}

int main()
{
    Thread_pool pool(2);
    pool.start();
    for (int i = 0; i < 100; i++)
    {
        Task *task = new Task();
        task->func = test;
        int *a = new int(i);
        task->arg = a;
        pool.Submit_task(task);
    }
    pool.stop();
}