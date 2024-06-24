#ifndef _ENUM_FOR_STACK_OF_TREES_H

#define _ENUM_FOR_STACK_OF_TREES_H


typedef struct _stack_tree_el stack_tree_el;

struct _stack_tree_el{
        tree val;
        stack_tree_el *prev;
};

typedef struct{
        stack_tree_el *top;
} stack_of_trees;

#endif
