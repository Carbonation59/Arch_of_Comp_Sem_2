#ifndef _VECTOR_NORM_H

#define _VECTOR_NORM_H

#include <stdbool.h>

typedef struct {
        int *buffer;
        int size;
        int cap;
        int first;
} vector_i;

void vi_create(vector_i *v);
void vi_destroy(vector_i *v);
int vi_size(vector_i *v);
bool vi_grow_buffer(vector_i *v);
bool vi_push_back(vector_i *v, int f);
int vi_get(vector_i *v, int i);
void vi_plus_one(vector_i *v, int i);

#endif
