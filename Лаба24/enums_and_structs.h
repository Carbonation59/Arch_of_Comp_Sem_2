#ifndef _ENUMS_AND_STRUCTS_H

#define _ENUMS_AND_STRUCTS_H

typedef enum {
        TOK_NONE,
        TOK_X,
        TOK_CONST,
        TOK_OP,
        TOK_LBR,
        TOK_RBR,
} tok_type;

typedef struct{
        tok_type type;
        double const_val;
        char op;
} token;

typedef enum {
        READ_TOK_SUCCESS=0,
        READ_TOK_EOF=-1,
        READ_TOK_EOE=-2,
        READ_TOK_ERROR_INVALID_CHAR=-3,
        READ_TOK_ERROR_UNEXPECTED_TOKEN=-4,
} read_tok_result;

typedef enum{
        READ_EXPRESSION_SUCCESS_EOF=1,
        READ_EXPRESSION_SUCCESS_EOE=2,
        READ_EXPRESSION_ERROR_INVALID_CHAR=-3,
        READ_EXPRESSION_ERROR_UNEXPECTED_TOKEN=-4,
} read_expression_result;

typedef enum{
        A_LOT_OF_RIGHT_BRACKETS=-1,
        A_LOT_OF_LEFT_BRACKETS=-2,
        SUCCESS_OF_MAKING_POLISH_NOTATION=1,
} polish_notation_result;


typedef enum{
        WRONG_NUMBER_OF_TERMS=-2,
        SUCCESS_OF_CREATING_TREE=1,
} create_tree_result;

typedef enum{
        DIVISION_ON_ZERO_IN_CALCULATION=-1,
        X_IN_CALCULATION=-2,
        DIVISION_ON_X=-3,
        COMPOSITION_OF_X=-4,
        X_IN_POWER=-5,
        SUCCESS_OF_SIMPLIFYING=1,
} simplifying_tree_result;

typedef struct{
        simplifying_tree_result station;
        double val;
} simplifying_tree_element;


//очередь

typedef struct _queue_tok_el queue_tok_el;

struct _queue_tok_el{
        token val;
        queue_tok_el *next;
};

typedef struct{
        queue_tok_el *first;
        queue_tok_el *last;
} queue_tok;

//дерево

typedef struct node node;
typedef node * tree;

struct node {
        token val;
        node *left;
        node *right;
};

//стэк


typedef struct _stack_tok_el stack_tok_el;

struct _stack_tok_el{
        token val;
        stack_tok_el *prev;
};

typedef struct{
        stack_tok_el *top;
} stack_tok;

//стэк деревьев
/*
typedef struct _stack_tree_el stack_tree_el;

struct _stack_tree_el{
        tree val;
        stack_tree_el *prev;
};

typedef struct{
        stack_tree_el *top;
} stack_of_trees;
*/
#endif
