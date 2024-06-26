#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        double *buffer;
        long long size;
        long long cap;
        long long first;
} vector_double;

void vd_create(vector_double *v);
void vd_destroy(vector_double *v);
long long vd_size(vector_double *v);
bool vd_grow_buffer(vector_double *v);
bool vd_push_back(vector_double *v, double f);
double vd_get(vector_double *v, long long i);
