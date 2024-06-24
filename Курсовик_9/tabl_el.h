#ifndef _TABL_EL_H

#define _TABL_EL_H

#include <stdbool.h>

typedef struct{
        char k1[28];
        int k2;
} key;

typedef struct{
        int size_of_k1;
        int size_of_val;
        char val[100];
        key key;
} tabl_el;

bool read_tabl_el(tabl_el *a);
bool read_key(key *a);
int keycmp(key a, key b);

#endif
