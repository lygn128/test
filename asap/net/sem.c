#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

struct queue
{
    int *arry;
    sem_t access;
    sem_t slots;
    sem_t items;
    int front;
    int back;
    u_int64_t nums;
};

void P(sem_t *sem)
{
    sem_wait(sem);
}

void V(sem_t *sem)
{
    sem_post(sem);
}

void init_queue(struct queue *qu, int slots)
{
    sem_init(&qu->access, 0, 1);
    sem_init(&qu->slots, 0, slots);
    sem_init(&qu->items, 0, 0);
    qu->nums = slots;
    qu->front = -1;
    qu->back = -1;
    qu->arry = calloc(slots, sizeof(int));
}

void insert_to(struct queue *qu, int val)
{
    P(&qu->slots);
    P(&qu->access);
    qu->arry[++qu->front % qu->nums] = val;
    V(&qu->access);
    //V(&qu->slots);
    V(&qu->items);
}

int get_from_queue(struct queue *qu)
{
    int ret;
    P(&qu->items);
    P(&qu->access);
    ret = qu->arry[++qu->back % qu->nums];
    V(&qu->access);
    V(&qu->items);
    V(&qu->slots);
    return ret;
}

struct queue aqu;
void *produce(void *args)
{
    struct queue *qu = (struct queue *)args;
    int i = 0;
    while (1)
    {
        insert_to(qu, i++);
        printf("insert %ld %d\n", time(NULL), i);
    }
}

void *consume(void *args)
{
    struct queue *qu = (struct queue *)args;
    while (1)
    {
        int val = get_from_queue(qu);
        printf("get val  %ld %d\n", time(NULL), val);
        sleep(1);
    }
}
int main()
{
    init_queue(&aqu, 100);
    pthread_t th1, th2;
    pthread_create(&th1, NULL, produce, &aqu);
    sleep(10);
    pthread_create(&th2, NULL, consume, &aqu);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
}