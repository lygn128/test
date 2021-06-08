#include "list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct mydata_s mydata_t;
struct mydata_s {
    _mylist_t list;
    int a;
};


struct xxx {
    int *a;
    int *b;
    int c;
    int d;
    int e;

};

int main() {
    mydata_t * head = (mydata_t*)malloc(sizeof(mydata_t));
    create_list(&(head->list));

    mydata_t * data1 = (mydata_t*)malloc(sizeof(mydata_t));
    data1->a = 100;

    insert_head(&head->list, &data1->list);

    printf("is empty %d\n", is_empty(&(head->list)));
    printf("size of %lu\n", sizeof(mydata_t));
    printf("size of %lu\n", sizeof(struct xxx));
}