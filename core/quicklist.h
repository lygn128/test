#ifndef __QUICKLIST_H__
#define __QUICKLIST_H__
typedef struct quicklistNode
{
    struct quicklistNode *prev;
    struct quicklistNode *next;
    void *data;
} quicklistNode;

typedef struct quicklist
{
    quicklistNode *head;
    quicklistNode *tail;

} quicklist;

typedef struct quicklistIter
{
    quicklistNode *current;
    int direction;

} quicklistIter;

quicklist *quicklistCreate(void);
void quicklistPushFront(quicklist *list, void *value);
quicklistIter *quicklistIterCreate(quicklist *list, int direction);
quicklistNode *quicklistIterNext(quicklistIter *iter);
#endif