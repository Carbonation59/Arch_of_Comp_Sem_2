#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

void task(list *l, unsigned int val){
        iter i=begin_iter(l);
        bool h=false;
        iter i1=end_iter(l);
        while(!iter_equal(i,end_iter(l))){
                if(iter_val(i)==val){
                        if(!iter_equal(iter_next(i),end_iter(l)) && iter_val(iter_next(i))!=val){
                                iter_remove(&i);
                                if(h==true){
                                        i=iter_next(i);
                                        iter_remove(&i1);
                                }
                                if(h!=true && !iter_equal(i,end_iter(l))){
                                        i=iter_next(i);
                                        i1=iter_next(i1);
                                }
                                h=false;
                        } else if(!iter_equal(iter_next(i),end_iter(l))){
                                i=iter_next(i);
                                iter_remove(&i1);
                                h=true;
                        } else {
                                if(h==true){
                                        i=iter_next(i);
                                        iter_remove(&i1);
                                } else {
                                        i=iter_next(i);
                                }
                        }
                } else if(!iter_equal(iter_next(i),end_iter(l)) && iter_val(iter_next(i))==val){
                                i=iter_next(i);
                                iter_remove(&i1);
                } else {
                        i=iter_next(i);
                        i1=iter_next(i1);
                }
        }
}

void usage(){
        printf("\nUSAGE:\n\na <EL> <POS> - add element on specified position.\nd <POS> - delete element for specified position.\n");
        printf("t <EL> - task: удалить из списка все элементы, предшествующие и последующие заданному значению.\n\n");
        printf("Possible values for <EL>: unsigned int\n");
        printf("Possible values for <POS>: int,'b' - back of list, 'f' - front of list\n\n");
        printf("p - print list.\n\nh - help.\n\n");
}

void reading(char t){
        while(t!='\n'){
                t=getchar();
        }
}

int main(){
        usage();
        list l;
        l_create(&l);
        char a;
        unsigned int val;
        int pos;
        char test;
        while(scanf("%c",&a)!=-1){
                while(a==' ' || a=='\n' || a=='\t'){
                        scanf("%c",&a);
                }
                test=getchar();
                if(a=='h' && (test==' ' || test=='\n' || test=='\t')){
                       if(test!='\n'){
                                scanf("%c",&test);
                                while(test==' ' || test=='\t'){
                                        scanf("%c",&test);
                                }
                        }
                        if(test!='\n'){
                                printf("Error: use 'h' without any arguments.\n");
                                reading(test);
                        } else {
                                usage();
                        }
                } else if(a=='a' && (test==' ' || test=='\n' || test=='\t')){
                        if(test!=' ' && test!='\t'){
                                printf("Error: wrong usage of command 'a'. Use 'h' for help.\n");
                                continue;
                        }
                        while(test==' ' || test=='\t'){
                                test=getchar();
                        }
                        if(test=='\n'){
                                printf("Error: lack of arguments for command 'a'. Use 'h' for help.\n");
                                continue;
                        } else if(test>='1' && test<='9'){
                                ungetc(test,stdin);
                                scanf("%u",&val);
                                test=getchar();
                        } else {
                                printf("Error: wrong value for 'a'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        }
                        if(test!=' ' && test!='\n' && test!='\t'){
                                printf("Error: wrong value for 'a'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        }
                        while(test==' ' || test=='\t'){
                                test=getchar();
                        }
                        if(test=='\n'){
                                printf("Error: lack of arguments for command 'a'. Use 'h' for help.\n");
                                continue;
                        }
                        if(test>='1' && test<='9'){
                                ungetc(test,stdin);
                                scanf("%d",&pos);
                                test=getchar();
                        } else if(test=='b'){
                                pos=l.size+1;
                                test=getchar();
                        } else if(test=='f'){
                                pos=1;
                                test=getchar();
                        } else {
                                printf("Error: wrong position for 'a'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        }
                        if(test!=' ' && test!='\n' && test!='\t'){
                                printf("Error: wrong position for 'a'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        }
                        while(test==' ' || test=='\t'){
                                test=getchar();
                        }
                        if(test!='\n'){
                                printf("Error: wrong number of arguments for 'a'. Use 'h' for help.\n");
                                reading(test);
                        } else {
                                if(pos>l.size+1){
                                        printf("Error: incorrect position for this list.\n");
                                } else if(l_insert(&l,val,pos)){
                                        printf("The addition was successful\n");
                                } else {
                                        printf("Error\n");
                                }
                        }
                } else if(a=='d' && (test==' ' || test=='\n' || test=='\t')){
                       if(test!=' ' && test!='\t'){
                                printf("Error: wrong usage of command 'd'. Use 'h' for help.\n");
                                continue;
                        }
                        while(test==' ' || test=='\t'){
                                scanf("%c",&test);
                        }
                        if(test=='\n'){
                                printf("Error: lack of arguments for command 'd'. Use 'h' for help.\n");
                                continue;
                        }
                        if(test>='1' && test<='9'){
                                ungetc(test,stdin);
                                scanf("%d",&pos);
                                test=getchar();
                        } else if(test=='b'){
                                pos=l.size;
                                test=getchar();
                        } else if(test=='f'){
                                pos=1;
                                test=getchar();
                        } else {
                                printf("Error: wrong position for 'd'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        }
                        if(test!=' ' && test!='\n' && test!='\t'){
                                printf("Error: wrong position for 'd'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        }
                        while(test==' ' || test=='\t'){
                                scanf("%c",&test);
                        }
                        if(test!='\n'){
                                printf("Error: wrong number of arguments for 'd'. Use 'h' for help.\n");
                                reading(test);
                        } else {
                                if(pos>l.size){
                                        printf("Error: incorrect position for this list.\n");
                                } else {
                                        l_remove(&l,pos);
                                        printf("The deletion was successful\n");
                                }
                        }
                } else if(a=='p' && (test==' ' || test=='\n' || test=='\t')){
                        while(test==' ' || test=='\t'){
                                scanf("%c",&test);
                        }
                        if(test!='\n'){
                                printf("Error: use 'p' without arguments.\n");
                                reading(test);
                        } else {
                                l_print(&l);
                        }
                } else if(a=='t' && (test==' ' || test=='\n' || test=='\t')){
                        if(test!=' ' && test!='\t'){
                                printf("Error: wrong usage of command 't'. Use 'h' for help.\n");
                                continue;
                        }
                        while(test==' ' || test=='\t'){
                                scanf("%c",&test);
                        }
                        if(test=='\n'){
                                printf("Error: lack of arguments for command 't'. Use 'h' for help.\n");
                                continue;
                        } else if(test>='1' && test<='9'){
                                ungetc(test,stdin);
                                scanf("%u",&val);
                                test=getchar();
                        } else {
                                printf("Error: wrong value for 't'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        }
                        if(test!=' ' && test!='\n' && test!='\t'){
                                printf("Error: wrong value for 't'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        }
                        while(test==' ' || test=='\t'){
                                scanf("%c",&test);
                        }
                        if(test!='\n'){
                                printf("Error: wrong number of arguments for command 't'. Use 'h' for help.\n");
                                reading(test);
                                continue;
                        } else {
                                task(&l,val);
                                printf("Task done\n");
                        }
                } else {
                        printf("Wrong key. Use 'h' for help\n");
                        reading(test);
                }
        }
        l_destroy(&l);
}

