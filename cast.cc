#include <iostream>
#include <unistd.h>
using namespace std;

class A
{
public:
    virtual void display()
    {
        std::cout << "class a" << std::endl;
    }
};

class B : public A
{
public:
    virtual void display()
    {
        std::cout << "class a" << std::endl;
    }
};
class C : public A
{
public:
    virtual void display()
    {
        std::cout << " class c" << std::endl;
    }
};
void testStatic(void *xx)
{
    A *a = static_cast<A *>(xx);
    a->display();
}

void testDyna(A *a)
{
    B *b = dynamic_cast<B *>(a);
    std::cout << "b is: " << b << std::endl;
    if (b)
    {
        b->display();
    }

    C *c = dynamic_cast<C *>(a);
    c->display();
}


class ListNode {
public:
    int val;
    ListNode * next;
public:
ListNode(int x):val(x),next(nullptr) {}
};


void readFileLatency(string file) {

} 

int main()
{
    //ListNode  node(1);
    //std::cout << node.val  << " " << node.next << std::endl;
    // A *a = new A();
    // testStatic(a);
    // B *b = new B();
    // testStatic(b);

    // C *c = new C();
    // testDyna(c);
}