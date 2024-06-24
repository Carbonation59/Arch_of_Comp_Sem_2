#include <stdbool.h>
#include <stdlib.h>
#include "enums_and_structs.h"
#include "stack_tok_list.h"

void st_create(stack_tok *s){
        s->top=NULL;
}

bool st_is_empty(stack_tok *s){
        return s->top==NULL;
}

bool st_push(stack_tok *s, token val){
        stack_tok_el *new_el=malloc(sizeof(stack_tok_el));
        if(new_el==NULL){
                return false;
        }
        new_el->val=val;
        new_el->prev=s->top;
        s->top=new_el;
        return true;
}

token st_pop(stack_tok *s){
        token el=s->top->val;
        stack_tok_el *tmp=s->top->prev;
        free(s->top);
        s->top=tmp;
        return el;
}

void st_destroy(stack_tok *s){
        while(!st_is_empty(s)){
                st_pop(s);
        }
}
