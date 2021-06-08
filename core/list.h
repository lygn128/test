typedef struct _mylist_s _mylist_t;
struct _mylist_s {
    _mylist_t *next;
    _mylist_t *prev;
};

#define create_list(q)    \
    (q)->next = q;     \
    (q)->prev = q;

#define insert_head(h, x)     \
    (x)->next = (h)->next;    \
    (x)->next->prev = x;      \
    (h)->next = x;            \
    (x->prev)

#define insert_tail(h, x)    \
    (x)->prev = (h)->prev;   \
    (x)->prev->next = h;     \
    (h)->prev = x;
#define is_empty(h)          \
    (h)->prev == (h)->next

#define remove_node(h, x)   \
    
