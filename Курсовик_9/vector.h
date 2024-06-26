#ifndef _VECTOR_H

#define _VECTOR_H

#include <stdbool.h>
#include "tabl_el.h"

typedef struct {
        tabl_el *buffer;
        int size;
        int cap;
        int first;
} vector_tabl_el;

void vt_create(vector_tabl_el *v);
void vt_destroy(vector_tabl_el *v);
int vt_size(vector_tabl_el *v);
bool vt_push_back(vector_tabl_el *v, tabl_el f);
tabl_el vt_get(vector_tabl_el *v, int i);
void print_tabl_el(tabl_el a);
void print_vector(vector_tabl_el *v);
void vt_set(vector_tabl_el *v,int i, tabl_el val);

#endif
