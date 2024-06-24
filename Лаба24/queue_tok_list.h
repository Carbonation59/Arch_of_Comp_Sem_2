#include <stdbool.h>
#include "enums_and_structs.h"

#ifndef _QUEUE_TOK_LIST_H

#define _QUEUE_TOK_LIST_H

void qt_create(queue_tok *q);
bool qt_is_empty(queue_tok *q);
bool qt_push(queue_tok *q, token val);
token qt_pop(queue_tok *q);
void qt_destroy(queue_tok *q);

#endif
