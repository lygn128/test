#include <stdio.h>
#include <stdlib.h>
#include "quicklist.h"

int main()
{
    quicklist *ls = quicklistCreate();

    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(*a));
        *a = i;
        quicklistPushFront(ls, a);
        }
    quicklistIter *it = quicklistIterCreate(ls, 1);
    while (it->current)
    {
        int *a = it->current->data;
        printf("a is %d\n", *a);
        quicklistIterNext(it);
    }
}