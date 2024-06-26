#ifndef _vector_tv_h_
#define _vector_tv_h_


#include "team_victories.h"


typedef struct {
        int size;
        team_victories *buffer;
} vector_tv;

void vector_tv_create(vector_tv *v);
void vector_tv_destroy(vector_tv *v);
bool vector_tv_resize(vector_tv *v, int new_size);
int vector_tv_size(vector_tv *v);
bool vector_tv_push(vector_tv *v, team_victories f);

#endif
