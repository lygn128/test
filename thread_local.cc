#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;


class Base {
public:
    Base() {
        std::cout << "base construct" << std::endl;
    }
};

class MyTest {
public:
    //thread_local Base base;
    MyTest() {
        std::cout << "MY test Construct " << std::endl;
    }
    void run() {
        thread_local Base base;
        std::cout << " local base is:" << std::endl;
    }
};

void *loop(void * args) {
    MyTest test;
    for(int i = 0; i < 10; i++) {
        test.run();
        sleep(1);
        std::cout << "tid is:" << pthread_self() << std::endl;
    }
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, loop, NULL);
    MyTest test;
    for(int i = 0; i < 10; i++) {
        test.run();
    }
    
    pthread_join(tid, NULL);
    pthread_create(&tid, NULL, loop, NULL);
    pthread_join(tid, NULL);





}