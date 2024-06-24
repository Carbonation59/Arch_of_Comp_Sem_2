#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

void vector_tv_create(vector_tv *v){
        v->size=0;
        v->buffer=NULL;
}

void vector_tv_destroy(vector_tv *v){
        v->size=0;
        free(v->buffer);
        v->buffer=NULL;
}

bool vector_tv_resize(vector_tv *v, int new_size){
        team_victories *n=realloc(v->buffer,sizeof(team_victories)*new_size);
        if(n!=NULL){
                v->size=new_size;
                v->buffer=n;
                return true;
        } else {
                return false;
        }
}

int vector_tv_size(vector_tv *v){
        return v->size;
}

bool vector_tv_push(vector_tv *v, team_victories f){
        if(!vector_tv_resize(v, (v->size)+1)){
                return false;
        }
        strcpy(v->buffer[(v->size)-1].team,f.team);
        v->buffer[(v->size)-1].victories=f.victories;
        return true;
}
