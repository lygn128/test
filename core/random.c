#include <stdlib.h>
#include <stdio.h>
static unsigned long x=123456789, y=362436069, z=521288629;

unsigned long xorshf96(void) {          //period 2^96-1
unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;

  return z;
}


int main() {
    for(int i = 0; i < 130; i++) {
        printf("------%lu", xorshf96());
    }
}