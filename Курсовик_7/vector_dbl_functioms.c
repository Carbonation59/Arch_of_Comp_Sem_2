#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

void vd_create(vector_double *v){
        v->size=0;
        v->first=0;
        v->cap=0;
        v->buffer=NULL;
}

void vd_destroy(vector_double *v){
        v->size=0;
        v->first=0;
        v->cap=0;
        free(v->buffer);
        v->buffer=NULL;
}

double vd_get(vector_double *v,long long i){
        return v->buffer[(v->first+i)%v->cap];
}

long long vd_size(vector_double *v){
        return v->size;
}

bool vd_grow_buffer(vector_double *v){
        long long tmp=v->cap*3/2;
        if(v->cap==0){
                tmp=9;
        }
        double *n=realloc(v->buffer,sizeof(double)*tmp);
        if(n==NULL){
                return false;
        } else {
                v->buffer=n;
                for(long long i=v->cap-v->first-1;i>=0;i--){
                        v->buffer[(tmp+i-(v->cap-v->first))%tmp]=v->buffer[(v->first+i)%tmp];
                        v->buffer[(v->first+i)%tmp]=0;
                }
                v->first=(tmp-(v->cap-v->first))%tmp;
                v->cap=tmp;
                return true;
        }
}

bool vd_push_back(vector_double *v,double val){
        if(v->size>=v->cap){
                if(!(vd_grow_buffer(v))){
                        return false;
                }
        }
        v->buffer[(v->first+v->size)%v->cap]=val;
        v->size++;
        return true;
}
