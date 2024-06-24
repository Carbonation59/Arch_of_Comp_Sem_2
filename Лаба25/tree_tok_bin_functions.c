#include <stdbool.h>
#include <stdlib.h>
#include "enums_and_structs.h"
#include "tree_tok_bin.h"

tree create_empty_tree(){
        return NULL;
}

void destroy(tree *t){
        free(*t);
        *t=NULL;
}

void clear_tree_recursive(tree *t){
        if(*t!=NULL){
                clear_tree_recursive(&(*t)->right);
                clear_tree_recursive(&(*t)->left);
                destroy(t);
        }
}

tree build_tree(tree left, token val, tree right){
        tree tmp=malloc(sizeof(node));
        tmp->left=left;
        tmp->right=right;
        tmp->val=val;
        return tmp;
}

bool tree_is_empty(tree t){
        return t==NULL;
}

token get_root(tree t){
        return t->val;
}

tree get_left(tree t){
        return t->left;
}

tree get_right(tree t){
        return t->right;
}
