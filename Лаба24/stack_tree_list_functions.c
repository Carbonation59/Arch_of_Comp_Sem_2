#include <stdbool.h>
#include <stdlib.h>
#include "enums_and_structs.h"
#include "stack_tree_list.h"
#include "enum_for_stack_of_trees.h"

void se_create(stack_of_trees *s){
        s->top=NULL;
}

bool se_is_empty(stack_of_trees *s){
        return s->top==NULL;
}

bool se_push(stack_of_trees *s, tree val){
        stack_tree_el *new_el=malloc(sizeof(stack_tree_el));
        if(new_el==NULL){
                return false;
        }
        new_el->val=val;
        new_el->prev=s->top;
        s->top=new_el;
        return true;
}

tree se_pop(stack_of_trees *s){
        tree el=s->top->val;
        stack_tree_el *tmp=s->top->prev;
        free(s->top);
        s->top=tmp;
        return el;
}

void se_destroy(stack_of_trees *s){
        while(!se_is_empty(s)){
                se_pop(s);
        }
}
