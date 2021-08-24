#include "quicklist.h"
#include <stdlib.h>

quicklist *quicklistCreate()
{
    quicklist *qu = (quicklist *)malloc(sizeof(*qu));
    qu->head = qu->tail = NULL;
    return qu;
}

void quicklistPushFront(quicklist *list, void *value)
{
    quicklistNode *node = (quicklistNode *)malloc(sizeof(*node));
    node->data = value;
    node->prev = NULL;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        quicklistNode *temp = list->head;
        temp->prev = node;
        node->next = temp;
        list->head = node;
    }
}

quicklistIter *quicklistIterCreate(quicklist *list, int direction)
{
    quicklistIter *it = malloc(sizeof(it));
    it->direction = direction;
    if (it->direction == 0)
    {
        it->current = list->head;
    }
    else
    {
        it->current = list->tail;
    }
}
quicklistNode *quicklistIterNext(quicklistIter *iter)
{
    switch (iter->direction)
    {
    case 0:
        if (iter->current == NULL)
            return NULL;
        iter->current = iter->current->next;
        return iter->current;
        break;

    default:
        if (iter->current == NULL)
            return NULL;
        iter->current = iter->current->prev;
        return iter->current;
        break;
    }
}
