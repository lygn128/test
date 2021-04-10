/* 验证智能指针的用法 */
#include <iostream>
#include <unistd.h>
#include <map>
#include <list>
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


int main()
{
    // LruCache<xxxx*> lru(1000);
    // for (int i = 0; i < 1000000; i++)
    // {
    //     lru.put(i, new xxxx());
    // }
    // return 0;
    std::list<std::shared_ptr<A>>  ls;
    std::cout << __LINE__  << " ---------" << std::endl;
    x(ls);
    std::cout << __LINE__  << " ---------" << std::endl;
    ls.push_back(o(3000));
    std::cout << __LINE__  << " ---------" << std::endl;
    o(4000);
    //std::shared_ptr<A> ptr = o(1000);
    std::cout << " hello world" << std::endl;
}