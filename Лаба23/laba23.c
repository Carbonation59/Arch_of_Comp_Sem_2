#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
        zero,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        ENUM_INVALID,
} numbers;

typedef struct node node;

struct node{
        node *first_child;
        node *next_bro;
        numbers val;
};

//очередь

typedef struct _queue_tree_el queue_tree_el;

struct _queue_tree_el{
        node *val;
        queue_tree_el *next;
};

typedef struct{
        queue_tree_el *first;
        queue_tree_el *last;
} queue_tree;

void qt_create(queue_tree *q){
        q->first=NULL;
        q->last=NULL;
}

bool qt_is_empty(queue_tree *q){
        return q->first==NULL;
}

bool qt_push(queue_tree *q, node *val){
        queue_tree_el *new_el=malloc(sizeof(queue_tree_el));
        if(new_el==NULL){
                return false;
        }
        new_el->val=val;
        new_el->next=NULL;
        if(qt_is_empty(q)){
                q->first=new_el;
                q->last=new_el;
                return true;
        }
        q->last->next=new_el;
        q->last=new_el;
        return true;
}

node *qt_pop(queue_tree *q){
        node *el=q->first->val;
        if(q->first==q->last){
                free(q->first);
                q->first=NULL;
                q->last=NULL;
                return el;
        }
        queue_tree_el *tmp=q->first->next;
        free(q->first);
        q->first=tmp;
        return el;
}

void qt_destroy(queue_tree *q){
        while(!qt_is_empty(q)){
                qt_pop(q);
        }
}

//добавление/удаление

bool add(node **t,numbers val,char *path, bool start){
        if(*path!='\0' && *path!='.' && *t==NULL){
                printf("Can't reach this path\n");
                return false;
        } else if(*path=='c'){
                return add(&(*t)->first_child,val,path+1,start);
        } else if(*path=='b'){
                return add(&(*t)->next_bro,val,path+1,start);
        } else if(*path=='\0' || (*path=='.' && start==true)){
                node *tmp=malloc(sizeof(node));
                if(tmp==NULL){
                        printf("Lack of memory\n");
                        return false;
                }
                tmp->val=val;
                tmp->first_child=NULL;
                tmp->next_bro=*t;
                *t=tmp;
                return true;
        } else {
                printf("Wrong path\n");
                return false;
        }
}

void destroy(node **t){
        if((*t)==NULL){
                return;
        }
        if((*t)->first_child!=NULL){
                destroy(&(*t)->first_child);
        }
        if((*t)->next_bro!=NULL){
                destroy(&(*t)->next_bro);
        }
        free(*t);
        *t=NULL;
        return;
}

bool delete_el(node **t,char *path, bool start){
        if(*t==NULL){
                printf("Can't reach this path\n");
                return false;
        } else if(*path=='c'){
                return delete_el(&(*t)->first_child,path+1,start);
        } else if(*path=='b'){
                return delete_el(&(*t)->next_bro,path+1,start);
        } else if(*path=='\0' || (*path=='.' && start==true)){
                node *tmp=(*t)->next_bro;
                destroy(&(*t)->first_child);
                free(*t);
                *t=tmp;
                return true;
        } else {
                printf("Wrong path\n");
                return false;
        }
}

//перевод из енама в цифру и обратно

numbers parse_enum_name(char *s){
        if(!strcmp(s, "zero")){
                return zero;
        } else if(!strcmp(s, "one")){
                return one;
        } else if(!strcmp(s, "two")){
                return two;
        } else if(!strcmp(s, "three")){
                return three;
        } else if(!strcmp(s, "four")){
                return four;
        } else if(!strcmp(s, "five")){
                return five;
        } else if(!strcmp(s, "six")){
                return six;
        } else if(!strcmp(s, "seven")){
                return seven;
        } else if(!strcmp(s, "eight")){
                return eight;
        } else if(!strcmp(s, "nine")){
                return nine;
        } else if(!strcmp(s, "ten")){
                return ten;
        } else {
                return ENUM_INVALID;
        }
}
char *get_enum_name(numbers a){
        if(a==zero){
                return "zero";
        } else if(a==one){
                return "one";
        } else if(a==two){
                return "two";
        } else if(a==three){
                return "three";
        } else if(a==four){
                return "four";
        } else if(a==five){
                return "five";
        } else if(a==six){
                return "six";
        } else if(a==seven){
                return "seven";
        } else if(a==eight){
                return "eight";
        } else if(a==nine){
                return "nine";
        } else {
                return "ten";
        }
}

//задание

int number_of_bros(node **t, int a){
        if(*t!=NULL){
                a++;
                return number_of_bros(&(*t)->next_bro,a);
        } else {
                return a;
        }
}

int task(node **t, int answer){
        if(*t==NULL){
                return answer;
        }
        int a=0;
        a=number_of_bros(&(*t)->first_child,a);
        if(a==(*t)->val){
                answer++;
        }
        answer=task(&(*t)->first_child,answer);
        answer=task(&(*t)->next_bro,answer);
        return answer;
}

//печать уровней через bfs

void push_bros(queue_tree *a, node *t){
        if(t==NULL){
                return;
        } else {
                qt_push(a,t);
                push_bros(a,t->next_bro);
        }
}

void print_bfs(node *t){
        if(t==NULL){
                return;
        }
        queue_tree a,b,c;
        qt_create(&a);
        qt_create(&b);
        qt_create(&c);
        node *tmp;
        push_bros(&a,t);
        while(!qt_is_empty(&a)){
                while(!qt_is_empty(&a)){
                        tmp=qt_pop(&a);
                        printf("%s ",get_enum_name(tmp->val));
                        push_bros(&b,tmp->first_child);
                }
                printf("\n");
                c=b;
                b=a;
                a=c;
        }
        qt_destroy(&a);
        qt_destroy(&b);
        qt_destroy(&c);
}

//стэк

typedef struct {
        node *t;
        bool child_done;
} dfs_el;

typedef struct _stack_tree_el stack_tree_el;

struct _stack_tree_el{
        dfs_el val;
        stack_tree_el *prev;
};

typedef struct{
        stack_tree_el *top;
} stack_dfs_el;

void sde_create(stack_dfs_el *s){
        s->top=NULL;
}

bool sde_is_empty(stack_dfs_el *s){
        return s->top==NULL;
}

bool sde_push(stack_dfs_el *s, dfs_el val){
        stack_tree_el *new_el=malloc(sizeof(stack_tree_el));
        if(new_el==NULL){
                return false;
        }
        new_el->val=val;
        new_el->prev=s->top;
        s->top=new_el;
        return true;
}

dfs_el sde_pop(stack_dfs_el *s){
        dfs_el el=s->top->val;
        stack_tree_el *tmp=s->top->prev;
        free(s->top);
        s->top=tmp;
        return el;
}

void sde_destroy(stack_dfs_el *s){
        while(!sde_is_empty(s)){
                sde_pop(s);
        }
}


//печать через dfs

void print_dfs(node *t){
        if(t==NULL){
                return;
        }
        stack_dfs_el s;
        sde_create(&s);
        dfs_el el;
        el.t=t;
        el.child_done=false;
        sde_push(&s,el);
        int tab=0;
        while(!sde_is_empty(&s)){
                dfs_el tmp=sde_pop(&s);
                if(!tmp.child_done){
                        for(int i=0;i<tab;i++){
                                printf("\t");
                        }
                        printf("%s\n",get_enum_name(tmp.t->val));
                        el.t=tmp.t;
                        el.child_done=true;
                        sde_push(&s,el);
                        if(tmp.t->first_child!=NULL){
                                tab++;
                                el.t=tmp.t->first_child;
                                el.child_done=false;
                                sde_push(&s,el);
                        }
                } else {
                        if(tmp.t->next_bro!=NULL){
                                el.t=tmp.t->next_bro;
                                el.child_done=false;
                                sde_push(&s,el);
                        } else {
                                tab--;
                        }
                }
        }
        sde_destroy(&s);
}

//USAGE

void usage(){
        printf("\nUSAGE:\n\na <EL> <PATH> - add element on specified path.\n\nd <PATH> - delete element for specified path.\n\nExample for path: cbcc ('.' - root).\n");
        printf("Example for el:\n\n");
        for(numbers i=zero;i!=ENUM_INVALID;i++){
                printf("%s\n",get_enum_name(i));
        }
        printf("\np dfs - print tree dfs.\np bfs - print tree bfs.\n\nt - task: Определить число вершин дерева, степень которых совпадает со значением эелемента.\n\nh - help.\n\n");
}


//мейн

int main(){
        usage();
        char a;
        numbers el;
        node *root=NULL;
        char number[100];
        char path[100];
        char test;
        char string[300];
        bool start;
        int answer=0;
        while(scanf("%c",&a)!=-1){
                scanf("%c",&test);
                if(a=='h' && (test==' ' || test=='\n' || test=='\t')){
                        if(test!='\n'){
                                scanf("%c",&test);
                                while(test==' ' || test=='\t'){
                                        scanf("%c",&test);
                                }
                        }
                        if(test!='\n'){
                                printf("Error: use 'h' without any arguments.\n");
                                fgets(string,300,stdin);
                        } else {
                                usage();
                        }
                } else if(a=='a' && (test==' ' || test=='\n' || test=='\t')){
                        start=false;
                        scanf("%s%s",number,path);
                        scanf("%c",&test);
                        while(test==' ' || test=='\t'){
                                scanf("%c",&test);
                        }
                        if(test!='\n'){
                                printf("Error: wrong number of arguments for 'a'. Use 'h' for help.\n");
                                fgets(string,300,stdin);
                        } else {
                                el=parse_enum_name(number);
                                if(el!=ENUM_INVALID){
                                        if(!strcmp(path,".")){
                                                start=true;
                                        }
                                        if(add(&root,el,path,start)){
                                                printf("The addition was successful\n");
                                        } else {
                                                printf("Error\n");
                                        }
                                } else {
                                        printf("Wrong value\n");
                                }
                        }
                } else if(a=='d' && (test==' ' || test=='\n' || test=='\t')){
                        start=false;
                        scanf("%s",path);
                        scanf("%c",&test);
                        while(test==' ' || test=='\t'){
                                scanf("%c",&test);
                        }
                        if(test!='\n'){
                                printf("Error: wrong number of arguments for 'd'. Use 'h' for help.\n");
                                fgets(string,300,stdin);
                        } else {
                                if(!strcmp(path,".")){
                                        start=true;
                                }
                                if(delete_el(&root,path,start)){
                                        printf("The deletion was successful\n");
                                } else {
                                        printf("Error\n");
                                }
                        }
                } else if(a=='p' && (test==' ' || test=='\n' || test=='\t')){
                        scanf("%s",path);
                        while(test==' ' || test=='\t'){
                                scanf("%c",&test);
                        }
                        if(test!='\n'){
                                printf("Error: wrong number of arguments for 'p'. Use 'h' for help\n");
                                fgets(string,300,stdin);
                        }
                        if(!strcmp(path,"dfs")){
                                print_dfs(root);
                        } else if(!strcmp(path,"bfs")){
                                print_bfs(root);
                        } else {
                                printf("Error: wrong variant of print. Use 'h' for help\n");
                        }
                } else if(a=='t' && (test==' ' || test=='\n' || test=='\t')){
                        if(test!='\n'){
                                scanf("%c",&test);
                                while(test==' ' || test=='\t'){
                                        scanf("%c",&test);
                                }
                        }
                        if(test!='\n'){
                                printf("Error: use 't' without any arguments.\n");
                                fgets(string,300,stdin);
                        } else {
                                printf("%d\n",task(&root,answer));
                        }
                } else {
                        printf("Wrong key. Use 'h' for help\n");
                        fgets(string,300,stdin);
                }
        }
        destroy(&root);
}
