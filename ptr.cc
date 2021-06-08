/* 验证智能指针的用法 */
#include <iostream>
#include <unistd.h>
#include <map>
#include <list>
#include <thread>
using namespace std;

class A
{
    int a;

public:
    A(int a)
    {
        this->a = a;
        std::cout << " construct class A:" << a << std::endl;
    }
    ~A()
    {
        std::cout << " destruct class A:" << a << std::endl;
    }
};

void x(std::list<std::shared_ptr<A>>  &ls)
{
    //A *x = new A(3);
    std::shared_ptr<A> ptr = std::make_shared<A>(1);
    ptr = std::make_shared<A>(2);
    ls.push_front(ptr);

}

std::shared_ptr<A> o(int a)
{
    return std::make_shared<A>(a);
}

class xxxx
{
public:
    int a;
    char b;
    long c;
};
template <class T>
//typedef typename std::vector<T>::iterator iterator;
class LruCache
{
    std::map<int, T> contents;
    std::list<int> lru;
    int cap;

public:
    LruCache<T>(int c)
    {
        cap = c;
    }
    int get(int key)
    {
    }
    int  put(int key, T val)
    {
        typename std::map<int, T>::iterator it1;
        it1 = contents.find(key);
        if (it1 == contents.end())
        {
            contents[key] = val;
            lru.push_front(key);
        }
        if (lru.size() > cap)
        {
            int x = lru.back();
            lru.pop_back();
            contents.erase(x);
        }
    }
};




void f1(int n) {
    for(int i = 0; i < 100;i++) {
        sleep(1);
        std::cout << " thread is:" << n << std::endl;
    }
}

void testThread() {
    std::thread t1(f1, 1);
    std::thread t2(f1, 100);
    std::thread t3(f1, 30);
}


void testThread2() {
    int a; 
    std::thread t1([](int a) {

    },std::ref(a));
    t1.join();
}

void increase(std::atomic<long> &at) {
    at++;
}
void testatomic() {
    std::atomic<long> xxx{0};

}


int main() {
    // srand(time(NULL));
    // for(int i = 0; i < 1000; i++) {
    //     std::cout << rand() %1000 << std::endl;
    // }
    //testThread2();
    testatomic();
}






