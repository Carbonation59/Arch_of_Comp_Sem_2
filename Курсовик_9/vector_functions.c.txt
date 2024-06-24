#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tabl_el.h"
#include "vector.h"

void vt_create(vector_tabl_el *v){
        v->size=0;
        v->first=0;
        v->cap=0;
        v->buffer=NULL;
}

void vt_destroy(vector_tabl_el *v){
        v->size=0;
        v->first=0;
        v->cap=0;
        free(v->buffer);
        v->buffer=NULL;
}

tabl_el vt_get(vector_tabl_el *v,int i){
        return v->buffer[(v->first+i)%v->cap];
}

void vt_set(vector_tabl_el *v,int i, tabl_el val){
        v->buffer[(v->first+i)%v->cap]=val;
}

int vt_size(vector_tabl_el *v){
        return v->size;
}

bool vt_grow_buffer(vector_tabl_el *v){
        int tmp=v->cap*3/2;
        if(v->cap==0){
                tmp=9;
        }
        tabl_el *n=realloc(v->buffer,sizeof(tabl_el)*tmp);
        if(n==NULL){
                return false;
        } else {
                v->buffer=n;
                for(int i=v->cap-v->first-1;i>=0;i--){
                        v->buffer[(tmp+i-(v->cap-v->first))%tmp]=v->buffer[(v->first+i)%tmp];
                }
                v->first=(tmp-(v->cap-v->first))%tmp;
                v->cap=tmp;
                return true;
        }
}

bool vt_push_back(vector_tabl_el *v, tabl_el val){
        if(v->size>=v->cap){
                if(!(vt_grow_buffer(v))){
                        return false;
                }
        }
        v->buffer[(v->first+v->size)%v->cap]=val;
        v->size++;
        return true;
}

void print_tabl_el(tabl_el a){
        for(int j=0;j<a.size_of_k1;j++){
                printf("%c",a.key.k1[j]);
        }
        printf("|%d|",a.key.k2);
        for(int j=0;j<a.size_of_val;j++){
                printf("%c",a.val[j]);
        }
        printf("\n");
}

void print_vector(vector_tabl_el *v){
        tabl_el a;
        for(int i=0;i<vt_size(v);i++){
                a=vt_get(v,i);
                print_tabl_el(a);
        }
        printf("\n");
}
