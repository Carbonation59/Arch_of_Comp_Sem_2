#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vector_norm.h"

void vi_create(vector_i *v){
        v->size=0;
        v->first=0;
        v->cap=0;
        v->buffer=NULL;
}

void vi_destroy(vector_i *v){
        v->size=0;
        v->first=0;
        v->cap=0;
        free(v->buffer);
        v->buffer=NULL;
}

void vi_plus_one(vector_i *v, int i){
        v->buffer[(v->first+i)%v->cap]++;
}

int vi_get(vector_i *v,int i){
        return v->buffer[(v->first+i)%v->cap];
}

int vi_size(vector_i *v){
        return v->size;
}

bool vi_grow_buffer(vector_i *v){
        int tmp=v->cap*3/2;
        if(v->cap==0){
                tmp=9;
        }
        int *n=realloc(v->buffer,sizeof(int)*tmp);
        if(n==NULL){
                return false;
        } else {
                v->buffer=n;
                for(int i=v->cap-v->first-1;i>=0;i--){
                        v->buffer[(tmp+i-(v->cap-v->first))%tmp]=v->buffer[(v->first+i)%tmp];
                        v->buffer[(v->first+i)%tmp]=0;
                }
                v->first=(tmp-(v->cap-v->first))%tmp;
                v->cap=tmp;
                return true;
        }
}

bool vi_push_back(vector_i *v,int val){
        if(v->size>=v->cap){
                if(!(vi_grow_buffer(v))){
                        return false;
                }
        }
        v->buffer[(v->first+v->size)%v->cap]=val;
        v->size++;
        return true;
}


