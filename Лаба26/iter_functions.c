#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

unsigned int iter_val(iter it){
        return it.l->buf[it.prev].val;
}

iter iter_next(iter it){
        if(it.prev==-1){
                it.prev=it.l->first;
        } else{
                it.prev=it.l->buf[it.prev].next;
        }
        return it;
}

void iter_swap(iter *it1, iter *it2){
        unsigned int c=iter_val(*it1);
        it1->l->buf[it1->prev].val=iter_val(*it2);
        it2->l->buf[it2->prev].val=c;
        return;
}

bool iter_equal(iter it1, iter it2){
        return it1.prev==it2.prev;
}

iter begin_iter(list *l){
        iter res;
        res.prev=l->first;
        res.l=l;
        return res;
}

iter end_iter(list *l){
        iter res;
        res.prev=-1;
        res.l=l;
        return res;
}

bool grow_buffer(list *l){
        list_el *tmp=realloc(l->buf,sizeof(list_el)*l->cap*3/2);
        if(tmp==NULL){
                return false;
        }
        l->buf=tmp;
        for(int i=l->cap;i<l->cap*3/2-1;i++){
                l->buf[i].next=i+1;
        }
        l->top_empty=l->cap;
        l->cap=l->cap*3/2;
        l->buf[l->cap-1].next=-1;
        return true;
}

bool iter_insert(iter it, unsigned int val){
        if(it.l->size+1==it.l->cap){
                if(!grow_buffer(it.l)){
                        return false;
                }
        }
        int tmp=it.l->top_empty;
        it.l->top_empty=it.l->buf[it.l->top_empty].next;
        it.l->buf[tmp].val=val;
        if(iter_equal(it,end_iter(it.l))){
                it.l->buf[tmp].next=it.l->first;
                it.l->first=tmp;
                if(l_is_empty(it.l)){
                        it.l->last=tmp;
                }
                it.l->size++;
                return true;
        }
        if(it.prev==it.l->last){
                it.l->last=tmp;
        }
        it.l->buf[tmp].next=it.l->buf[it.prev].next;
        it.l->buf[it.prev].next=tmp;
        it.l->size++;
        return true;
}

void iter_remove(iter *it){
        if(iter_equal(*it,end_iter(it->l))){
                int tmp=it->l->first;
                it->l->first=it->l->buf[tmp].next;
                it->l->buf[tmp].next=it->l->top_empty;
                it->l->top_empty=tmp;
                it->l->size--;
                if(l_is_empty(it->l)){
                        it->l->last=it->l->first;
                }
                return;
        }
        if(it->l->buf[it->prev].next==it->l->last){
                it->l->last=it->prev;
        }
        int tmp=it->l->buf[it->prev].next;
        it->l->buf[it->prev].next=it->l->buf[tmp].next;
        it->l->buf[tmp].next=it->l->top_empty;
        it->l->top_empty=tmp;
        it->l->size--;
}
