#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>


#define x(a) var_##a


struct __attribute__ ((__packed__)) sdshdr32 {
   uint32_t len;
   uint32_t alloc;
   //unsigned char flags;
   char buff[];   

};

int main() {
   int x(a);
   int x(b);
   int x(c);
   double a = 0.44444444444443;
   double b = 0.44444444444442;
   printf(" size of %d\n", sizeof(struct sdshdr32));
   printf("is equal %d\n", a == b);

}