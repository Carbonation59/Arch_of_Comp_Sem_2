#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "enums_and_structs.h"
#include "queue_tok_list.h"
#include "tree_tok_bin.h"
#include "stack_tree_list.h"
#include "stack_tok_list.h"

void example(){
        printf("\nExample of input information:\n");
        printf("\nStripe1: 3*x^3+12*x^2+7*x^4+3*x^1+1\n");
        printf("Stripe2: 12*x^2+1*x+5*x^3+0*x^4+12\n\n");
}

double epsilone(){
        double a=1;
        double c;
        while(a+1>1){
                c=a;
                a=a/2;
        }
        return c;
}

double e;

read_tok_result read_token(token *cur, tok_type prev){
        char a;
        double b;
        a=getchar();
        while(a==' ' || a=='\t'){
                a=getchar();
        }
        if(a>='0' && a<='9'){
                if(prev==TOK_X || prev==TOK_CONST || prev==TOK_RBR){
                        return READ_TOK_ERROR_UNEXPECTED_TOKEN;
                }
                ungetc(a,stdin);
                scanf("%lf",&b);
                cur->type=TOK_CONST;
                cur->const_val=b;
        } else if(a=='x'){
                if(prev==TOK_X || prev==TOK_CONST || prev==TOK_RBR){
                        return READ_TOK_ERROR_UNEXPECTED_TOKEN;
                }
                cur->type=TOK_X;
        } else if(a=='+' || a=='-' || a=='*' || a=='/' || a=='^'){
                cur->type=TOK_OP;
                if(a=='-' && (prev==TOK_NONE || prev==TOK_LBR || prev==TOK_OP)){
                        cur->op='~';
                        return READ_TOK_SUCCESS;
                }
                if(prev==TOK_NONE || prev==TOK_OP || prev==TOK_LBR){
                        return READ_TOK_ERROR_UNEXPECTED_TOKEN;
                }
                cur->op=a;
        } else if(a=='('){
                if(prev!=TOK_NONE && prev!=TOK_OP && prev!=TOK_LBR){
                        return READ_TOK_ERROR_UNEXPECTED_TOKEN;
                }
                cur->type=TOK_LBR;
                cur->op=a;
        } else if(a==')'){
                if(prev==TOK_NONE || prev==TOK_OP){
                        return READ_TOK_ERROR_UNEXPECTED_TOKEN;
                }
                cur->type=TOK_RBR;
                cur->op=a;
        } else if(a=='\n'){
                return READ_TOK_EOE;
        } else if(a==EOF){
                return READ_TOK_EOF;
        } else {
                return READ_TOK_ERROR_INVALID_CHAR;
        }
        return READ_TOK_SUCCESS;
}

read_expression_result read_expression(queue_tok *q){
        token a;
        tok_type prev_a;
        prev_a=TOK_NONE;
        read_expression_result report=READ_EXPRESSION_SUCCESS_EOF;
        for(;;){
                read_tok_result status=read_token(&a,prev_a);
                if(status==READ_TOK_SUCCESS){
                        qt_push(q,a);
                        prev_a=a.type;
                } else if(status==READ_TOK_EOF){
                        if(report==READ_EXPRESSION_SUCCESS_EOF){
                                return  READ_EXPRESSION_SUCCESS_EOF;
                        }
                        return report;
                } else if(status==READ_TOK_EOE){
                        if(report==READ_EXPRESSION_SUCCESS_EOF){
                                return READ_EXPRESSION_SUCCESS_EOE;
                        }
                        return report;
                } else if(status==READ_TOK_ERROR_UNEXPECTED_TOKEN && report==READ_EXPRESSION_SUCCESS_EOF){
                        report=READ_EXPRESSION_ERROR_UNEXPECTED_TOKEN;
                } else if(report==READ_EXPRESSION_SUCCESS_EOF) {
                        report=READ_EXPRESSION_ERROR_INVALID_CHAR;
                }
        }
}

polish_notation_result make_polish_notation(queue_tok *q){
        stack_tok s;
        st_create(&s);
        queue_tok Q;
        qt_create(&Q);
        token a,b;
        while(!qt_is_empty(q)){
                a=qt_pop(q);
                if(a.type==TOK_CONST || a.type==TOK_X){
                        qt_push(&Q,a);
                } else if(a.type==TOK_LBR){
                        st_push(&s,a);
                } else if(a.type==TOK_RBR){
                        while(a.type!=TOK_LBR){
                                if(st_is_empty(&s)){
                                        st_destroy(&s);
                                        qt_destroy(&Q);
                                        return A_LOT_OF_RIGHT_BRACKETS;
                                }
                                a=st_pop(&s);
                                if(a.type!=TOK_LBR){
                                        qt_push(&Q,a);
                                }
                        }
                } else {
                        if(st_is_empty(&s) || a.op=='^'){
                                st_push(&s,a);
                        } else {
                                b=st_pop(&s);
                                if(a.op=='+' || a.op=='-'){
                                        while(b.op!='(' && !st_is_empty(&s)){
                                                qt_push(&Q,b);
                                                b=st_pop(&s);
                                        }
                                        if(st_is_empty(&s)){
                                                if(b.op!='('){
                                                        qt_push(&Q,b);
                                                        st_push(&s,a);
                                                } else {
                                                        st_push(&s,b);
                                                        st_push(&s,a);
                                                }
                                        } else {
                                                st_push(&s,b);
                                                st_push(&s,a);
                                        }
                                } else if(a.op=='*' || a.op=='/'){
                                        while((b.op=='~' || b.op== '^' || b.op=='*' || b.op=='/') && !st_is_empty(&s)){
                                                qt_push(&Q,b);
                                                b=st_pop(&s);
                                        }
                                        if(st_is_empty(&s)){
                                                if(b.op=='~' || b.op== '^' || b.op=='*' || b.op=='/'){
                                                        qt_push(&Q,b);
                                                        st_push(&s,a);
                                                } else {
                                                        st_push(&s,b);
                                                        st_push(&s,a);
                                                }
                                        } else {
                                                st_push(&s,b);
                                                st_push(&s,a);
                                        }
                                } else {
                                        while(b.op=='^' && !st_is_empty(&s)){
                                                qt_push(&Q,b);
                                                b=st_pop(&s);
                                        }
                                        if(st_is_empty(&s)){
                                                if(b.op=='^'){
                                                        qt_push(&Q,b);
                                                        st_push(&s,a);
                                                } else {
                                                        st_push(&s,b);
                                                        st_push(&s,a);
                                                }
                                        } else {
                                                st_push(&s,b);
                                                st_push(&s,a);
                                        }
                                }
                        }
                }
        }
        while(!qt_is_empty(&Q)){
                qt_push(q,qt_pop(&Q));
        }
        while(!st_is_empty(&s)){
                a=st_pop(&s);
                if(a.type==TOK_LBR){
                        return A_LOT_OF_LEFT_BRACKETS;
                }
                qt_push(q,a);
        }
        st_destroy(&s);
        qt_destroy(&Q);
        return SUCCESS_OF_MAKING_POLISH_NOTATION;
}

void print_tree(tree t, int h){
        if(t!=NULL){
                print_tree(t->right,h+1);
                for(int i=0;i<h;i++){
                        printf("        ");
                }
                token a=t->val;
                if(a.type==TOK_X){
                        printf("x\n");
                } else if(a.type==TOK_CONST){
                        printf("%fl\n",a.const_val);
                } else {
                        printf("%c\n",a.op);
                }
                print_tree(t->left,h+1);
        }
}

simplifying_tree_element simplifying_tree(tree *t1){
        if((*t1)==NULL){
                return (simplifying_tree_element){SUCCESS_OF_SIMPLIFYING,0};
        }
        if((*t1)->val.type==TOK_OP){
                simplifying_tree_element l=simplifying_tree(&(*t1)->left);
                simplifying_tree_element r=simplifying_tree(&(*t1)->right);
                if((*t1)->val.op=='*' && r.station==X_IN_CALCULATION && l.station==X_IN_CALCULATION){
                        return (simplifying_tree_element){COMPOSITION_OF_X,0};
                } else if((*t1)->val.op=='^' && r.station==X_IN_CALCULATION){
                        return (simplifying_tree_element){X_IN_POWER,0};
                } else if((*t1)->val.op=='/' && r.station==X_IN_CALCULATION){
                        return (simplifying_tree_element){DIVISION_ON_X,0};
                } else if(l.station!=SUCCESS_OF_SIMPLIFYING){
                        return l;
                } else if(r.station!=SUCCESS_OF_SIMPLIFYING){
                        return r;
                } else if((*t1)->val.op=='~'){
                        return (simplifying_tree_element){SUCCESS_OF_SIMPLIFYING,r.val*(-1)};
                } else if((*t1)->val.op=='+'){
                        return (simplifying_tree_element){SUCCESS_OF_SIMPLIFYING,r.val+l.val};
                } else if((*t1)->val.op=='-'){
                        return (simplifying_tree_element){SUCCESS_OF_SIMPLIFYING,l.val-r.val};
                } else if((*t1)->val.op=='*'){
                        return (simplifying_tree_element){SUCCESS_OF_SIMPLIFYING,l.val*r.val};
                } else if((*t1)->val.op=='/'){
                        if((r.val-0)<e && r.val>=0){
                                return (simplifying_tree_element){DIVISION_ON_ZERO_IN_CALCULATION,0};
                        }
                        return (simplifying_tree_element){SUCCESS_OF_SIMPLIFYING,l.val/r.val};
                } else{
                        return (simplifying_tree_element){SUCCESS_OF_SIMPLIFYING,pow(l.val,r.val)};
                }
        } else if((*t1)->val.type==TOK_X){
                return (simplifying_tree_element){X_IN_CALCULATION,0};
        } else{
                return (simplifying_tree_element){SUCCESS_OF_SIMPLIFYING,(*t1)->val.const_val};
        }
}

create_tree_result create_tree(queue_tok *q, tree *t1){
        tree t;
        stack_of_trees s;
        se_create(&s);
        token a;
        tree r,l;
        while(!qt_is_empty(q)){
                a=qt_pop(q);
                if(a.type==TOK_CONST || a.type==TOK_X){
                        t=build_tree(NULL,a,NULL);
                        se_push(&s,t);
                } else{
                        if(a.op=='+' || a.op=='-'){
                                if(se_is_empty(&s)){
                                        return WRONG_NUMBER_OF_TERMS;
                                }
                                r=se_pop(&s);
                                if(se_is_empty(&s)){
                                        return WRONG_NUMBER_OF_TERMS;
                                }
                                l=se_pop(&s);
                                t=build_tree(l,a,r);
                                se_push(&s,t);
                        } else if(a.op=='*' || a.op=='/'){
                                if(se_is_empty(&s)){
                                        return WRONG_NUMBER_OF_TERMS;
                                }
                                r=se_pop(&s);
                                if(se_is_empty(&s)){
                                        return WRONG_NUMBER_OF_TERMS;
                                }
                                l=se_pop(&s);
                                t=build_tree(l,a,r);
                                se_push(&s,t);
                        } else if(a.op=='~'){
                                if(se_is_empty(&s)){
                                        return WRONG_NUMBER_OF_TERMS;
                                }
                                r=se_pop(&s);
                                t=build_tree(NULL,a,r);
                                se_push(&s,t);
                        } else {
                                if(se_is_empty(&s)){
                                        return WRONG_NUMBER_OF_TERMS;
                                }
                                r=se_pop(&s);
                                if(se_is_empty(&s)){
                                        return WRONG_NUMBER_OF_TERMS;
                                }
                                l=se_pop(&s);
                                t=build_tree(l,a,r);
                                se_push(&s,t);
                        }
                }
        }
        t=se_pop(&s);
        *t1=t;
        se_destroy(&s);
        return SUCCESS_OF_CREATING_TREE;
}

simplifying_tree_result simpling(tree *t){
        simplifying_tree_element g;
        simplifying_tree_result a,b;
        if((*t)!=NULL){
                a=simpling(&(*t)->left);
                b=simpling(&(*t)->right);
                if((*t)->val.type==TOK_OP){
                        if(a!=SUCCESS_OF_SIMPLIFYING && a!=X_IN_CALCULATION && (*t)->val.op!='~'){
                                return a;
                        }
                        if(b!=SUCCESS_OF_SIMPLIFYING && b!=X_IN_CALCULATION){
                                return b;
                        }
                        g=simplifying_tree(t);
                        if((*t)->val.op=='^' && (*t)->right->val.type==TOK_CONST && ((*t)->right->val.const_val-0)<e && (*t)->right->val.const_val>=0){
                                (*t)->val.type=TOK_CONST;
                                (*t)->val.const_val=1;
                                clear_tree_recursive(&(*t)->right);
                                clear_tree_recursive(&(*t)->left);
                        } else if((*t)->val.op=='^' && (*t)->right->val.type==TOK_CONST && ((*t)->right->val.const_val-0)<(e+1) && (*t)->right->val.const_val>=1){
                                clear_tree_recursive(&(*t)->right);
                                tree tmp=(*t)->left;
                                free(*t);
                                *t=tmp;
                        } else if(g.station==SUCCESS_OF_SIMPLIFYING){
                                (*t)->val.type=TOK_CONST;
                                (*t)->val.const_val=g.val;
                                clear_tree_recursive(&(*t)->right);
                                clear_tree_recursive(&(*t)->left);
                        }
                }
                if((*t)->val.type==TOK_CONST || (*t)->val.type==TOK_X){
                        return SUCCESS_OF_SIMPLIFYING;
                }
        }
        return g.station;
}

bool bringing_coefficients_of_x(tree *t, bool *x, bool *del, double *koef,double power){
        bool x1=false,x2=false,del1=false,del2=false;
        double koef1=0,koef2=0;
        token s;
        s.type=TOK_OP;
        s.op='~';
        if((*t)!=NULL){
                if(!bringing_coefficients_of_x(&(*t)->left,&x1,&del1,&koef1,power)){
                        *koef=koef1;
                        return false;
                }
                if(!bringing_coefficients_of_x(&(*t)->right,&x2,&del2,&koef2,power)){
                        *koef=koef2;
                        return false;
                }
                if((*t)->val.type==TOK_X && (power-1)<e && power>e){
                        *koef=1;
                        *x=true;
                        return true;
                }
                if((*t)->val.type==TOK_CONST && (power-0)<e){
                        *koef=(*t)->val.const_val;
                        *x=true;
                        return true;
                }
                if((*t)->val.type==TOK_OP && (*t)->val.op!='~' && (*t)->right->val.type==TOK_CONST && (power-0)<e && ((*t)->val.op=='+' || (*t)->val.op=='-' || (*t)->val.op=='~')){
                        *koef=koef2;
                        *x=true;
                }
                if((*t)->val.type==TOK_OP && (*t)->val.op!='~' && (*t)->left->val.type==TOK_CONST && (power-0)<e && ((*t)->val.op=='+' || (*t)->val.op=='-' || (*t)->val.op=='~')){
                        *koef=koef1;
                        *x=true;
                }
                if((*t)->val.type==TOK_OP && (*t)->val.op=='^'){
                        if((*t)->left->val.type==TOK_X && del1==false){
                                if((*t)->right->val.const_val-ceil((*t)->right->val.const_val)<0){
                                        *koef=20;
                                        return false;
                                }
                                if((*t)->right->val.const_val<0){
                                        *koef=40;
                                        return false;
                                }
                                if(((*t)->right->val.const_val-power-0)<e){
                                        *x=true;
                                        *koef=1;
                                }
                        } else {
                                *koef=10;
                                return false;
                        }
                } else if((*t)->val.type==TOK_OP && (*t)->val.op=='~' && x2==true){
                        *koef=koef2*(-1);
                        *x=true;
                        *del=del2;
                } else if((*t)->val.type==TOK_OP && (*t)->val.op=='*'){
                        if((power-0)<e){
                                if(x1==true && x2==true){
                                        *koef=koef1*koef2;
                                        *x=true;
                                        *del=del1+del2;
                                }
                        } else if(x1==true){
                                *koef=koef1*(*t)->right->val.const_val;
                                *x=true;
                                *del=del1;
                        } else if(x2==true){
                                *koef=koef2*(*t)->left->val.const_val;
                                *x=true;
                                *del=del2;
                        }

                } else if((*t)->val.type==TOK_OP && (*t)->val.op=='/'){
                        if(((*t)->right->val.const_val-0)<e && (*t)->right->val.const_val>=0){
                                *koef=0;
                                return false;
                        }
                        if((power-0)<e){
                                if(x1==true && x2==true){
                                        *koef=koef1/koef2;
                                        *x=true;
                                        *del=del1+del2;
                                }
                        } else if(x1==true){
                                *koef=koef1/(*t)->right->val.const_val;
                                *x=true;
                                *del=del1;
                        }
                } else if((*t)->val.type==TOK_OP && (*t)->val.op=='+'){
                        if(x1==true && del1==false && x2==true && del2==false){
                                *koef=koef1+koef2;
                                *x=true;
                        } else if(x1==true && del1==false && x2==true){
                                *koef=koef1+koef2;
                                clear_tree_recursive(&(*t)->left);
                                tree tmp=(*t)->right;
                                free(*t);
                                *t=tmp;
                                *x=true;
                                *del=true;
                        } else if(x2==true && del2==false && x1==true){
                                *koef=koef1+koef2;
                                clear_tree_recursive(&(*t)->right);
                                tree tmp=(*t)->left;
                                free(*t);
                                *t=tmp;
                                *x=true;
                                *del=true;
                        } else if(x1==true && x2==true){
                                *koef=koef1+koef2;
                                *x=true;
                                *del=true;
                        } else if(x1==true){
                                *koef=koef1;
                                if(del1==false){
                                        clear_tree_recursive(&(*t)->left);
                                        tree tmp=(*t)->right;
                                        free(*t);
                                        *t=tmp;
                                }
                                *x=true;
                                *del=true;
                        } else if(x2==true){
                                *koef=koef2;
                                if(del2==false){
                                        clear_tree_recursive(&(*t)->right);
                                        tree tmp=(*t)->left;
                                        free(*t);
                                        *t=tmp;
                                }
                                *x=true;
                                *del=true;
                        }
                } else if((*t)->val.type==TOK_OP && (*t)->val.op=='-'){
                        if(x1==true && del1==false && x2==true && del2==false){
                                *koef=koef1-koef2;
                                *x=true;
                        } else if(x1==true && del1==false && x2==true){
                                *koef=koef1-koef2;
                                clear_tree_recursive(&(*t)->left);
                                tree tmp=(*t)->right;
                                free(*t);
                                *t=tmp;
                                *x=true;
                                *del=true;
                        } else if(x2==true && del2==false && x1==true){
                                *koef=koef1-koef2;
                                clear_tree_recursive(&(*t)->right);
                                tree tmp=(*t)->left;
                                free(*t);
                                *t=tmp;
                                *x=true;
                                *del=true;
                        } else if(x1==true && x2==true){
                                *koef=koef1-koef2;
                                *x=true;
                                *del=true;
                        } else if(x1==true){
                                *koef=koef1;
                                if(del1==false){
                                        clear_tree_recursive(&(*t)->left);
                                        (*t)->val=s;
                                }
                                *x=true;
                                *del=true;
                        } else if(x2==true){
                                *koef=koef2*(-1);
                                if(del2==false){
                                        clear_tree_recursive(&(*t)->right);
                                        tree tmp=(*t)->left;
                                        free(*t);
                                        *t=tmp;
                                }
                                *x=true;
                                *del=true;
                       }
                }
        }
        return true;
}

bool finding_koef(tree *t,double power, double *a){
        if(*t==NULL){
                return false;
        }
        if((*t)->right==NULL){
                if(finding_koef(&(*t)->left,power,a)){
                        return true;
                } else {
                        return false;
                }
        }
        if((*t)->val.op=='*'){
                if(((*t)->left->right->val.const_val-power-0)<e && ((*t)->left->right->val.const_val-power)>=0){
                        *a=(*t)->right->val.const_val;
                        return true;
                } else {
                        return false;
                }
        }
        if(((*t)->right->left->right->val.const_val-power-0)<e && ((*t)->right->left->right->val.const_val-power)>=0){
                *a=(*t)->right->right->val.const_val;
                *t=(*t)->left;
                return true;
        }
        if(((*t)->right->left->right->val.const_val-power-0)>e){
                if(finding_koef(&(*t)->left,power,a)){
                        return true;
                } else {
                        return false;
                }
        }
        if(((*t)->right->left->right->val.const_val-power-0)<0){
                return false;
        }
        return false;
}

bool status_checker_1(read_expression_result s, queue_tok *q){
        if(s==READ_EXPRESSION_ERROR_INVALID_CHAR){
                printf("Error: input information have invalid char ");
                return true;
        }
        if(s==READ_EXPRESSION_ERROR_UNEXPECTED_TOKEN){
                printf("Error: input information have wrong order ");
                return true;
        }
        if(qt_is_empty(q)){
                printf("Error: no polynomial ");
                return true;
        }
        return false;
}

bool status_checker_2(polish_notation_result s, queue_tok *q){
        if(s==A_LOT_OF_RIGHT_BRACKETS){
                printf("Error: input information have a lot of right brackets ");
                return true;
        }
        if(s==A_LOT_OF_LEFT_BRACKETS){
                printf("Error: input information have a lot of left brackets ");
                return true;
        }
        if(qt_is_empty(q)){
                printf("Error: no polynomial ");
                return true;
        }
        return false;
}

bool status_checker_3(create_tree_result s){
        if(s==WRONG_NUMBER_OF_TERMS){
                printf("Error: wrong number of terms and operations ");
                return true;
        }
        return false;
}

bool status_checker_4(simplifying_tree_result s){
        if(s==X_IN_POWER){
                printf("Error: exponentiation in undifined power ");
                return true;
        }
        if(s==DIVISION_ON_X){
                printf("Error: division by x is not allowed ");
                return true;
        }
        if(s==COMPOSITION_OF_X){
                printf("Error: compostition of x is not allowed ");
                return true;
        }
        if(s==DIVISION_ON_ZERO_IN_CALCULATION){
                printf("Error: divinision on zero ");
                return true;
        }
        return false;
}

bool status_checker_5(bool s,double k){
        if(!s && (k-0)<e){
                printf("Error: divinision on zero ");
                return true;
        }
        if(!s && k>35){
                printf("Error: exponentiation in negative power ");
                return true;
        }
        if(!s && k>15){
                printf("Error: exponentiation in non-inveger power ");
                return true;
        }
        if(!s){
                printf("Error: several powers of x ");
                return true;
        }
        return false;
}

int main(){
        example();
        e=epsilone();
        queue_tok q1;
        qt_create(&q1);
        read_expression_result status1=read_expression(&q1);
        if(status_checker_1(status1,&q1)){
                printf("(Line 1)\n");
                return 0;
        }
        polish_notation_result status2=make_polish_notation(&q1);
        if(status_checker_2(status2,&q1)){
                printf("(Line 1)\n");
                return 0;
        }
        tree t1;
        create_tree_result status3=create_tree(&q1,&t1);
        if(status_checker_3(status3)){
                printf("(Line 1)\n");
                return 0;
        }
        simplifying_tree_result status4=simpling(&t1);
        if(status_checker_4(status4)){
                printf("(Line 1)\n");
                return 0;
        }
        double power=0;
        tree main1=NULL;
        while(t1!=NULL){
                bool x=false,del=false;
                double koef;
                bool z=bringing_coefficients_of_x(&t1,&x,&del,&koef,power);
                if(status_checker_5(z,koef)){
                        printf("(Line 1)\n");
                        return 0;
                }
                if(x){
                        token f,g,h,j,k,l;
                        tree F,G,H,J,K;
                        f.type=TOK_X;
                        g.type=TOK_OP;
                        g.op='*';
                        l.type=TOK_OP;
                        l.op='+';
                        h.type=TOK_OP;
                        h.op='^';
                        j.type=TOK_CONST;
                        k.type=TOK_CONST;
                        F=build_tree(NULL,f,NULL);
                        j.const_val=koef;
                        k.const_val=power;
                        K=build_tree(NULL,k,NULL);
                        J=build_tree(NULL,j,NULL);
                        H=build_tree(F,h,K);
                        G=build_tree(H,g,J);
                        if(x==true && del==false){
                                clear_tree_recursive(&t1);
                        }
                        if(main1==NULL){
                                main1=G;
                        } else {
                                main1=build_tree(main1,l,G);
                        }
                }
                power++;
        }

//второй многочлен

        queue_tok q2;
        qt_create(&q2);
        read_expression_result Status1=read_expression(&q2);
        if(status_checker_1(Status1,&q2)){
                printf("(Line 2)\n");
                return 0;
        }
        polish_notation_result Status2=make_polish_notation(&q2);
        if(status_checker_2(Status2,&q2)){
                printf("(Line 2)\n");
                return 0;
        }
        tree t2;
        create_tree_result Status3=create_tree(&q2,&t2);
        if(status_checker_3(Status3)){
                printf("(Line 2)\n");
                return 0;
        }
        simplifying_tree_result Status4=simpling(&t2);
        if(status_checker_4(Status4)){
                printf("(Line 2)\n");
                return 0;
        }
        power=0;
        tree main2=NULL;
        while(t2!=NULL){
                bool x=false,del=false;
                double koef;
                bool z=bringing_coefficients_of_x(&t2,&x,&del,&koef,power);
                if(status_checker_5(z,koef)){
                        printf("(Line 2)\n");
                        return 0;
                }
                if(x){
                        token f1,g1,h1,j1,k1,l1;
                        tree F1,G1,H1,J1,K1;
                        f1.type=TOK_X;
                        g1.type=TOK_OP;
                        g1.op='*';
                        l1.type=TOK_OP;
                        l1.op='+';
                        h1.type=TOK_OP;
                        h1.op='^';
                        j1.type=TOK_CONST;
                        k1.type=TOK_CONST;
                        F1=build_tree(NULL,f1,NULL);
                        j1.const_val=koef;
                        k1.const_val=power;
                        K1=build_tree(NULL,k1,NULL);
                        J1=build_tree(NULL,j1,NULL);
                        H1=build_tree(F1,h1,K1);
                        G1=build_tree(H1,g1,J1);
                        if(x==true && del==false){
                                clear_tree_recursive(&t2);
                        }
                        if(main2==NULL){
                                main2=G1;
                        } else {
                                main2=build_tree(main2,l1,G1);
                        }
                }
                power++;
        }
        power=0;
        double alpha,beta,ceta;
        if(main1->val.op=='*'){
                alpha=main1->left->right->val.const_val;
        } else {
                alpha=main1->right->left->right->val.const_val;
        }
        if(main2->val.op=='*'){
                beta=main2->left->right->val.const_val;
        } else {
                beta=main2->right->left->right->val.const_val;
        }
        if(alpha>beta){
                ceta=alpha;
        } else {
                ceta=beta;
        }
        printf("\nPolinominal MAX:");
        tree main=NULL;
        while(power<ceta+1){
                double one,two;
                double max_el;
                bool A,B;
                A=finding_koef(&main1,power,&one);
                B=finding_koef(&main2,power,&two);
                if(!A){
                        one=0;
                }
                if(!B){
                        two=0;
                }
                if(A || B){
                        if(one>=two){
                                max_el=one;
                        } else{
                                max_el=two;
                        }
                        if(power-0<e || max_el<0){
                                printf("%fl*x^%fl",max_el,power);
                        } else {
                                printf("+%fl*x^%fl",max_el,power);
                        }
                        token f2,g2,h2,j2,k2,l2;
                        tree F2,G2,H2,J2,K2;
                        f2.type=TOK_X;
                        g2.type=TOK_OP;
                        g2.op='*';
                        l2.type=TOK_OP;
                        l2.op='+';
                        h2.type=TOK_OP;
                        h2.op='^';
                        j2.type=TOK_CONST;
                        k2.type=TOK_CONST;
                        F2=build_tree(NULL,f2,NULL);
                        j2.const_val=max_el;
                        k2.const_val=power;
                        K2=build_tree(NULL,k2,NULL);
                        J2=build_tree(NULL,j2,NULL);
                        H2=build_tree(F2,h2,K2);
                        G2=build_tree(H2,g2,J2);
                        if(main==NULL){
                                main=G2;
                        } else {
                                main=build_tree(main,l2,G2);
                        }
                }
                power++;
        }
        printf("\nTree of polinominal:\n\n");
        print_tree(main,0);
        qt_destroy(&q1);
        qt_destroy(&q2);
        clear_tree_recursive(&t1);
        clear_tree_recursive(&t2);
        clear_tree_recursive(&main1);
        clear_tree_recursive(&main2);
        clear_tree_recursive(&main);
}
