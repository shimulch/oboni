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


/*---------- ADD IDENTIFIER IN BST --------------*/

void identifier_bst_add(char* key, char* value){
    I_BST* newOne = calloc(1,sizeof(I_BST));
    strcpy(newOne->key, key);
    strcpy(newOne->value, value);
    newOne->left = NULL;
    newOne->right = NULL;
    if(!i_bst){
        free(i_bst);
        i_bst = newOne;

        return;
    }
    I_BST* current = i_bst;
    while(1){
        int compared_value = strcmp(current->key, key);
        if( compared_value < 0){
            if(current->left == NULL){
                current->left = newOne;
                break;
            }else{
                current = current->left;
            }
        }else if(compared_value > 0){
            if(current->right == NULL){
                current->right = newOne;
                break;
            }else {
                current = current->right;
            }
        }else{

            strcpy(current->value, value);
            break;
        }
    }
}

I_BST* identifier_bst_get(char* key) {
    if(!i_bst) return NULL;
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
