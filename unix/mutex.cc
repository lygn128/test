#include <iostream>
#include <pthread.h>
using namespace std;

template<class T>
class Cirque {
   T* buff;
   int  
}

struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} ready = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

void wait() {
    pthread_mutex_lock(&ready.mutex);
    pthread_cond_wait(&ready.cond, &ready.mutex);
    pthread_mutex_unlock(&ready.mutex);
}
int main() {
    std::cout << "hello world" << std::endl;
}
