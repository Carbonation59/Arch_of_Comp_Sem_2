#include <stdbool.h>
#include "enums_and_structs.h"

#ifndef _STACK_TOK_LIST_H

#define _STACK_TOK_LIST_H

void st_create(stack_tok *s);
bool st_is_empty(stack_tok *s);
bool st_push(stack_tok *s, token val);
token st_pop(stack_tok *s);
void st_destroy(stack_tok *s);

#endif
