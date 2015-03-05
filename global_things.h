#ifndef GLOBAL_THINGS_H_INCLUDED
#define GLOBAL_THINGS_H_INCLUDED

#include "grammer.h"

#define INITIAL_CAPACITY 1000
#define DATA_TABLE_INITIAL_CAPACITY 20
#define MAXIMUM_COLUMN_SIZE 1000

typedef struct  {
    int token_id;
    char* value;
    TOKEN_TYPE token_type;
} TOKEN;

typedef struct {
    TOKEN* ARRAY;
    int capacity;
    int length;
} TOKEN_ARRAY;


typedef struct IDENTIFIER_BST I_BST;
struct IDENTIFIER_BST{
    char key[50];
    char value[100];
    I_BST *left, *right;
};

typedef struct AST_NODE_STRUCTURE AST_NODE;
struct AST_NODE_STRUCTURE {
    AST_NODE_TYPE node_type;
    TOKEN token;
    AST_NODE* childs[10];
};

I_BST *i_bst;

AST_NODE *ast_root;

TOKEN_TYPE token_type;
TOKEN_ARRAY token_array;

char current_line[MAXIMUM_COLUMN_SIZE];

int global_current_scope;

void token_array_init(TOKEN_ARRAY *t_array);
void token_array_append(TOKEN_ARRAY *t_array, TOKEN token);
TOKEN token_array_get(TOKEN_ARRAY *t, int index);
void double_token_capacity(TOKEN_ARRAY *t);
void free_token_array(TOKEN_ARRAY *t);




void identifier_bst_add(char* key, char* value);
I_BST* identifier_bst_get(char* key);
#endif // GLOBAL_THINGS_H_INCLUDED
