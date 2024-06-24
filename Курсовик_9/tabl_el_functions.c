#include <stdio.h>
#include <stdbool.h>
#include "tabl_el.h"

bool read_tabl_el(tabl_el *a){
        for(int i=0;i<sizeof(a->key.k1);i++){
                a->key.k1[i]=' ';
        }
        char w;
        a->size_of_k1=0;
        for(int i=0;i<sizeof(a->key.k1);i++){
                w=getchar();
                if(w=='|'){
                        break;
                }
                if(w==EOF){
                        return false;
                }
                a->key.k1[i]=w;
                a->size_of_k1++;
        }
        scanf("%d",&a->key.k2);
        w=getchar();
        if(w==EOF){
                return false;
        }
        a->size_of_val=0;
        for(int i=0;i<sizeof(a->val)-1;i++){
                w=getchar();
                if(w=='\n'){
                        break;
                }
                if(w==EOF){
                        return false;
                }
                a->val[i]=w;
                a->size_of_val++;
        }
        return true;
}

bool read_key(key *a){
        for(int i=0;i<sizeof(a->k1);i++){
                a->k1[i]=' ';
        }
        char w;
        for(int i=0;i<sizeof(a->k1);i++){
                w=getchar();
                if(w=='|'){
                        break;
                }
                if(w==EOF){
                        return false;
                }
                a->k1[i]=w;
        }
        scanf("%d",&a->k2);
        getchar();
        return true;
}

int keycmp(key a, key b){
        for(int i=0;i<sizeof(a.k1);i++){
                if(a.k1[i]>b.k1[i]){
                        return -1;
                } else if(a.k1[i]<b.k1[i]){
                        return 1;
                }
        }
        if(a.k2>b.k2){
                return -1;
        } else if(a.k2<b.k2){
                return 1;
        }
        return 0;
}
