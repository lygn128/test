#include <iostream>
using namespace std;
class A {
    public:
    A() {
        std::cout << "construct A" << std::endl;
    }
    static void xx(void*arg) {
        std::cout << __func__ << " " << __LINE__ << std::endl;
    }
};






// class B {
//     public:
//     A a;
//     B(int x) {
//         //a = A(1);
//         std::cout << "construct B" << std::endl;
//     }

// };
// class C:public A {
//     public:
//     C():A::A() {
//         std::cout << "construct c" << std::endl;
//     }
// };


void test(void * arg) {
    std::cout << __func__ << std::endl;
}

typedef void (*myfunc)(void * arg);
int main() {
    // B b;
    //C c;
    //A a(0);
    myfunc x = test;
    x(NULL);
    x = &(A::xx);
    x(NULL);

}