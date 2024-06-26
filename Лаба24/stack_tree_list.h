#include <stdbool.h>
#include "enums_and_structs.h"
#include "enum_for_stack_of_trees.h"

#ifndef _STACK_TREE_LIST_H

#define _STACK_TREE_LIST_H

void se_create(stack_of_trees *s);
bool se_is_empty(stack_of_trees *s);
bool se_push(stack_of_trees *s, tree val);
tree se_pop(stack_of_trees *s);
void se_destroy(stack_of_trees *s);

#endif
