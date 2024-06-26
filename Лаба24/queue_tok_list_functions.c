#include <stdbool.h>
#include <stdlib.h>
#include "queue_tok_list.h"
#include "enums_and_structs.h"

void qt_create(queue_tok *q){
        q->first=NULL;
        q->last=NULL;
}

bool qt_is_empty(queue_tok *q){
        return q->first==NULL;
}

bool qt_push(queue_tok *q, token val){
        queue_tok_el *new_el=malloc(sizeof(queue_tok_el));
        if(new_el==NULL){
                return false;
        }
        new_el->val=val;
        new_el->next=NULL;
        if(qt_is_empty(q)){
                q->first=new_el;
                q->last=new_el;
                return true;
        }
        q->last->next=new_el;
        q->last=new_el;
        return true;
}

token qt_pop(queue_tok *q){
        token el=q->first->val;
        if(q->first==q->last){
                free(q->first);
                q->first=NULL;
                q->last=NULL;
                return el;
        }
        queue_tok_el *tmp=q->first->next;
        free(q->first);
        q->first=tmp;
        return el;
}

void qt_destroy(queue_tok *q){
        while(!qt_is_empty(q)){
                qt_pop(q);
        }
}
