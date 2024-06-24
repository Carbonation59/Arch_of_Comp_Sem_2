#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector_ll.h"

void vll_create(vector_ll *v){
        v->size=0;
        v->first=0;
        v->cap=0;
        v->buffer=NULL;
}

void vll_destroy(vector_ll *v){
        v->size=0;
        v->first=0;
        v->cap=0;
        free(v->buffer);
        v->buffer=NULL;
}

long long vll_get(vector_ll *v,long long i){
        return v->buffer[(v->first+i)%v->cap];
}

long long vll_size(vector_ll *v){
        return v->size;
}

bool vll_grow_buffer(vector_ll *v){
        long long tmp=v->cap*3/2;
        if(v->cap==0){
                tmp=9;
        }
        long long *n=realloc(v->buffer,sizeof(long long)*tmp);
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

bool vll_push_back(vector_ll *v,long long val){
        if(v->size>=v->cap){
                if(!(vll_grow_buffer(v))){
                        return false;
                }
        }
        v->buffer[(v->first+v->size)%v->cap]=val;
        v->size++;
        return true;
}
