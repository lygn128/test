#include <iostream>
using namespace std;


class A {
    virtual void funcA() {

    }

    virtual  void  funcB() {

    }

    virtual  void  funcc() {

    }


};

typedef void (*myfunc)(void * arg);
int main() {
    // std::cout << a1() + a2() << std::endl;
    // arry[9] = 10;
    // test_exter();

    int * a = new int;
    free(a);

    std::cout << sizeof(A) << std::endl;

}