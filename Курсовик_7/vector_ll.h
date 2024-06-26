#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        long long *buffer;
        long long size;
        long long cap;
        long long first;
} vector_ll;

void vll_create(vector_ll *v);
void vll_destroy(vector_ll *v);
long long vll_size(vector_ll *v);
bool vll_grow_buffer(vector_ll *v);
bool vll_push_back(vector_ll *v, long long f);
long long vll_get(vector_ll *v, long long i);
