#include <stdbool.h>
#include "enums_and_structs.h"

#ifndef _TREE_TOK_BIN_H

#define _TREE_TOK_BIN_H

tree create_empty_tree();
void destroy(tree *t);
void clear_tree_recursive(tree *t);
tree build_tree(tree left, token val, tree right);
bool tree_is_empty(tree t);
token get_root(tree t);
tree get_left(tree t);
tree get_right(tree t);

#endif
