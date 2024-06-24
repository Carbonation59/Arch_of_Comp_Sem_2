#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

bool l_create(list *l){
        l->first=-1;
        l->last=-1;
        l->size=0;
        l->cap=10;
        l->top_empty=0;
        list_el *tmp=malloc(sizeof(list_el)*l->cap);
        if(tmp==NULL){
                return false;
        }
        l->buf=tmp;
        for(int i=0;i<l->cap-1;i++){
                l->buf[i].next=i+1;
        }
        l->buf[l->cap-1].next=-1;
        return true;
}

bool l_is_empty(list *l){
        return l->size==0;
}

iter find_iter(list *l, int i){
        if(i==1){
                return end_iter(l);
        }
        iter tmp=begin_iter(l);
        for(int j=1;j<i-1;j++){
                tmp=iter_next(tmp);
        }
        return tmp;
}

bool l_insert(list *l, unsigned int val, int i){
        iter tmp=find_iter(l,i);
        if(!iter_insert(tmp,val)){
                return false;
        }
        return true;
}

void l_remove(list *l, int i){
        iter tmp=find_iter(l,i);
        iter_remove(&tmp);
}

void l_print(list *l){
        for(iter i=begin_iter(l);!iter_equal(i,end_iter(l));i=iter_next(i)){
                printf("%u ",iter_val(i));
        }
        printf("\n");
}

void l_destroy(list *l){
        l->first=-1;
        l->last=-1;
        l->size=0;
        l->cap=0;
        l->top_empty=0;
        free(l->buf);
}
