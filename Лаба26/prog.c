#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void procedure(iter *k){
        iter o;
        for(iter i=begin_iter(k->l);!iter_equal(iter_next(i),*k);i=iter_next(i)){
                iter i1=iter_next(i);
                if(iter_val(i)>iter_val(i1)){
                        iter_swap(&i,&i1);
                }
                o=iter_next(i);
        }
        *k=o;
}


void buble_sort(list *l){
        iter k=end_iter(l);
        for(int j=0;j<l->size;j++){
                procedure(&k);
        }
}

int main(){
        list l;
        l_create(&l);
        unsigned int a;
        while(scanf("%u",&a)==1){
                iter_insert(end_iter(&l),a);
        }
        buble_sort(&l);
        l_print(&l);
}
