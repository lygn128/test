#include <thread>
#include <iostream>
#include <unistd.h>

using namespace std;


void f1(int n) {
    for(int i = 0; i <  10; i++) {
        sleep(1);
        std::cout << " i is :" << i << std::endl;
    }
}

int main() {
    // std::thread t1(f1, 0);
    // t1.join();
    std::cout << " finished\n" << std::endl;
    std::cout << (-1>>2) << " " << (1<<35)  << std::endl;
    std::cout << sizeof(long)  <<  " " << sizeof(long long) <<   " " << sizeof(int) << std::endl;

    int a = -1;
    std::cout << (unsigned int)(a) << "   " <<   (-1 < 0)<< std::endl;
}