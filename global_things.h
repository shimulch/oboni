#ifndef GLOBAL_THINGS_H_INCLUDED
#define GLOBAL_THINGS_H_INCLUDED

#include "grammer.h"

#define INITIAL_CAPACITY 1000
#define DATA_TABLE_INITIAL_CAPACITY 20
#define MAXIMUM_COLUMN_SIZE 1000

typedef struct  {
    int token_id;
    int value_id;
    TOKEN_TYPE token_type;
} TOKEN;

typedef struct {
    TOKEN* ARRAY;
    int capacity;
    int length;
} TOKEN_ARRAY;

typedef struct {
    TOKEN_TYPE type;
    char value[50];
} HASH_TABLE_DATA;

typedef struct {
    HASH_TABLE_DATA* ARRAY;
    int capacity;
    int length;
} HASH_TABLE;

typedef struct IDENTIFIER_BST I_BST;
struct IDENTIFIER_BST{
    char key[50];
    char value[100];
    I_BST *left, *right;
} ;

I_BST *i_bst;

TOKEN_TYPE token_type;
TOKEN_ARRAY token_array;
HASH_TABLE data_table;
char current_line[MAXIMUM_COLUMN_SIZE];



void token_array_init(TOKEN_ARRAY *t_array);
void token_array_append(TOKEN_ARRAY *t_array, TOKEN token);
TOKEN token_array_get(TOKEN_ARRAY *t, int index);
void double_token_capacity(TOKEN_ARRAY *t);
void free_token_array(TOKEN_ARRAY *t);

void hash_table_init(HASH_TABLE *h_table);
void hash_table_append(HASH_TABLE *h_table, HASH_TABLE_DATA hash_table_data);
HASH_TABLE_DATA hash_table_get(HASH_TABLE *h_table, int index);
void hash_table_set(HASH_TABLE *h_table, int index, HASH_TABLE_DATA value);
void double_hash_table_capacity(HASH_TABLE *h_table);
void free_hash_table(HASH_TABLE *h_table);



void identifier_bst_add(char* key, char* value);
I_BST* identifier_bst_get(char* key);
#endif // GLOBAL_THINGS_H_INCLUDED
