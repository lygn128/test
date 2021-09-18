#include <stdlib.h>
#include <stdio.h>

struct bit_x {
    int a:4;
    int b:4;
    int c:4;
    int d:4;
    int e:4;
    int f:4;

};


int main() {
    // int arry[50][50];
    // printf("size of arry %lu\n", sizeof(arry));
    // int a = 7;
    // return  ++a + a++;
    
    struct bit_x x;
    x.a = 10;
    printf("size of %d  %d\n", sizeof(struct bit_x), x.a);
    

    int a = 0x01020304;

    //int a[10];
    //char b = 1;
    //printf("%d\n", a&(0xFF));

}