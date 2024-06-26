#ifndef _LIST_H

#define _LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct{
        unsigned int val;
        int next;
} list_el;

typedef struct{
        int first;
        int last;
        int size;
        int cap;
        list_el* buf;
        int top_empty;
} list;

typedef struct{
        int prev;
        list *l;
} iter;

bool l_create(list *l);
bool l_is_empty(list *l);
void iter_swap(iter *it1, iter *it2);
iter find_iter(list *l, int i);
bool l_insert(list *l, unsigned int val, int i);
void l_remove(list *l, int i);
void l_print(list *l);
void l_destroy(list *l);
unsigned int iter_val(iter it);
iter iter_next(iter it);
bool iter_equal(iter it1, iter it2);
iter begin_iter(list *l);
iter end_iter(list *l);
bool iter_insert(iter it, unsigned int val);
void iter_remove(iter *it);

#endif
