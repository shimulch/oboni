#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "global_things.h"
#include "error_report.h"

/*--------- INITIALIZE DYNAMIC TOKEN ARRAY --------------*/
void token_array_init(TOKEN_ARRAY *t_array){
    t_array->capacity = INITIAL_CAPACITY;
    t_array->length = 0;
    t_array->ARRAY = malloc(sizeof(TOKEN)*t_array->capacity);
}


/*--------- APPEND A TOKEN IN TOKEN ARRAY --------------*/
void token_array_append(TOKEN_ARRAY *t_array, TOKEN token){
    double_token_capacity(t_array);
    //printf("GOT HIT with token type %d pos: %d\n", token.token_type, t_array->length);
    t_array->ARRAY[t_array->length] = token;
    t_array->length = t_array->length + 1;
}


/*--------- IF CAPACITY FULL DOUBLE IT --------------*/
void double_token_capacity(TOKEN_ARRAY *t_array){
    if(t_array->length >= t_array->capacity){
        //printf("DOUBLING\n");
        t_array->capacity *= 2;
        t_array->ARRAY = realloc(t_array->ARRAY, sizeof(TOKEN) * t_array->capacity);
    }
}


/*---------- GET A TOKEN FROM TOKEN ARRAY -------------*/
TOKEN token_array_get(TOKEN_ARRAY *t_array, int index){
    if(index >= t_array->length || index < 0) exit(1);
    return t_array->ARRAY[index];
}

/*---------- CLEAN TOKEN ARRAY -------------*/
void free_token_array(TOKEN_ARRAY *t_array) {
  free(t_array->ARRAY);
}







/*--------- INITIALIZE DYNAMIC HASH TABLE --------------*/
void hash_table_init(HASH_TABLE *h_table){
    h_table->capacity = DATA_TABLE_INITIAL_CAPACITY;
    h_table->length = 0;
    h_table->ARRAY = malloc(sizeof(HASH_TABLE_DATA)*h_table->capacity);
}

/*--------- APPEND A VALUE IN HASH TABLE --------------*/
void hash_table_append(HASH_TABLE *h_table, HASH_TABLE_DATA hash_table_data){
    double_hash_table_capacity(h_table);
    //printf("GOT HIT with token type %d pos: %d\n", token.token_type, t_array->length);
    h_table->ARRAY[h_table->length] = hash_table_data;
    h_table->length = h_table->length + 1;
}

/*--------- IF CAPACITY FULL DOUBLE IT --------------*/
void double_hash_table_capacity(HASH_TABLE *h_table){
    if(h_table->length >= h_table->capacity){
        //printf("DOUBLING\n");
        h_table->capacity *= 2;
        h_table->ARRAY = realloc(h_table->ARRAY, sizeof(HASH_TABLE_DATA) * h_table->capacity);
    }
}


/*--------- SET VALUE TO SOME POSITION --------------*/
void hash_table_set(HASH_TABLE *h_table, int index, HASH_TABLE_DATA value) {
  while (index >= h_table->length) {
    HASH_TABLE_DATA hash_table_data;
    hash_table_append(h_table, hash_table_data);
  }
  h_table->ARRAY[index] = value;
}


/*---------- GET A HASH TABLE DATA FROM HASH TABLE -------------*/
HASH_TABLE_DATA hash_table_get(HASH_TABLE *h_table, int index){
    if(index >= h_table->length || index < 0){
        show_error_and_exit(DATA_TABLE_OUT_OF_BOUND, 0);
    }
    return h_table->ARRAY[index];
}

/*---------- CLEAN HASH TABLE -------------*/
void free_hash_table(HASH_TABLE *h_table) {
  free(h_table->ARRAY);
}


/*---------- ADD IDENTIFIER IN BST --------------*/

void identifier_bst_add(char* key, char* value){
    I_BST* newOne = malloc(sizeof(I_BST));
    strcpy(newOne->key, key);
    strcpy(newOne->value, value);
    if(i_bst == NULL){
        i_bst = newOne;
        return;
    }
    I_BST* current = i_bst;
    while(1){
        if(strcmp(current->key, key) <= 0){
            if(current->left == NULL){
                current->left = newOne;
                break;
            }else{
                current = current->left;
            }
        }else{
            if(current->right == NULL){
                current->right = newOne;
                break;
            }else {
                current = current->right;
            }
        }
    }
}

I_BST* identifier_bst_get(char* key) {
    I_BST *newOne = NULL;
    I_BST* current = i_bst;
    while(1){
        int cmp_result = strcmp(current->key, key);
        if(cmp_result < 0){
            if(current->left == NULL){
                break;
            }else{
                current = current->left;
            }
        }else if(cmp_result > 0){
            if(current->right == NULL){
                break;
            }else {
                current = current->right;
            }
        }else{
            newOne = current;
            break;
        }
    }

    return newOne;
}
