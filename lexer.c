#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"
#include "error_report.h"
#include "global_things.h"
#include "fsm.h"

int total_tokens = 0;
char chunk[MAXIMUM_COLUMN_SIZE] = "";
int multiple_new_line = 0;
int value_id = 0;
/*-------- READ SOURCE FILE AND TOKENIZE ----------------------*/
void read_file(char* file_name){
    file_input_handler = fopen(file_name, "r");
    if(file_input_handler == NULL) show_error_and_exit(SOURCE_NOT_FOUND, 0);

    token_array_init(&token_array);
    hash_table_init(&data_table);

    while(fgets(current_line, MAXIMUM_COLUMN_SIZE, file_input_handler) != NULL){
            tokenizer(current_line);
    }

    if(token_array.ARRAY[token_array.length-1].token_type != NEWLINE){
        add_token(NEWLINE);
    }
    fclose(file_input_handler);
}


/*---------------- TOKENIZE A LINE ----------------------------*/
void tokenizer(){
    int x = 0, len = strlen(current_line);

    while(x < len){
        char ch = current_line[x];

        int got_token = 0;
        if(ch == '\n') {
            x++;
            if(multiple_new_line == 0){
                add_token_chunk();
                add_token(NEWLINE);
                multiple_new_line++;
            }
            continue;
        }

        multiple_new_line = 0;

        switch(ch){

            case '+':
                add_token_chunk();
                add_token(ADDITION_OPERATOR);
                got_token = 1;
                break;

            case '-':
                add_token_chunk();
                add_token(SUBSTRUCTION_OPERATOR);
                got_token = 1;
                break;

            case '*':
                add_token_chunk();
                add_token(MULTIPLICATION_OPERATOR);
                got_token = 1;
                break;

            case '/':
                add_token_chunk();
                add_token(DIVISION_OPERATOR);
                got_token = 1;
                break;

            case '=':
                add_token_chunk();
                if(x+1 < len){
                    if(current_line[x+1] == '='){
                        add_token(EQ_OPERATOR);
                        x++;
                    }else{
                        add_token(ASSIGNMENT_OPERATOR);
                    }
                }else
                    add_token(ASSIGNMENT_OPERATOR);
                got_token = 1;
                break;

            case '(':
                add_token_chunk();
                add_token(LP);
                got_token = 1;
                break;

             case ')':
                add_token_chunk();
                add_token(RP);
                got_token = 1;
                break;

            case '{':
                add_token_chunk();
                add_token(LCB);
                got_token = 1;
                break;

             case '}':
                add_token_chunk();
                add_token(RCB);
                got_token = 1;
                break;

            case '<':
                add_token_chunk();
                if(x+1 < len){
                    if(current_line[x+1] == '='){
                        add_token(LEQ_OPERATOR);
                        x++;
                    }else if(current_line[x+1] == '>'){
                        add_token(NE_OPERATOR);
                        x++;
                    }
                    else {
                        add_token(LT_OPERATOR);
                    }
                }else {
                        add_token(LT_OPERATOR);
                }
                got_token = 1;
                break;

            case '>':
                add_token_chunk();
                if(x+1 < len){
                    if(current_line[x+1] == '='){
                        add_token(BEQ_OPERATOR);
                        x++;
                    }else {
                        add_token(BT_OPERATOR);
                    }
                }else{
                    add_token(BT_OPERATOR);
                }
                got_token = 1;
                break;

            case '\t':
            case ' ':
                add_token_chunk();
                got_token = 1;
                break;

            default:
                break;
        }


        if(!got_token){

            strncat(chunk,&ch, 1);
            //puts(chunk);
        }else{
            strcpy(chunk, "");
        }

        x++;
    }
}


/*------------- CREATE A TOKEN AND ADD TO TOKEN ARRAY--------------*/
void add_token(TOKEN_TYPE token_type){
    TOKEN token;
    token.token_id = total_tokens++;
    if(token_type == IDENTIFIER || token_type == NUMBER){
        token.value_id = value_id;
    }
    token.token_type = token_type;
    token_array_append(&token_array, token);
}

void add_token_chunk(){
    //puts(chunk);
    //printf("%d \n", strlen(chunk));
    /*
    int i = 0;
    for(; i<strlen(chunk); i++){
        printf(" %c %d", chunk[i], chunk[i]);
    }

    puts("");
    */
    if(strcmp(chunk, "var") == 0){
        add_token(VAR);
        strcpy(chunk, "");
    }else if(strcmp(chunk, "if") == 0){
        add_token(IF);
        strcpy(chunk, "");
    }else if(strcmp(chunk, "when") == 0){
        add_token(WHEN);
        strcpy(chunk, "");
    }else if(fsm_identifier_check(chunk, strlen(chunk))){
        add_token(IDENTIFIER);
        add_value(IDENTIFIER);
        strcpy(chunk, "");
    }else if(fsm_number_check(chunk, strlen(chunk))){
        add_token(NUMBER);
        add_value(NUMBER);
        strcpy(chunk, "");
    }

}



void add_value(TOKEN_TYPE token_type) {
    HASH_TABLE_DATA hash_table_value;

    hash_table_value.type = IDENTIFIER;
    strcpy(hash_table_value.value, chunk);
    hash_table_append(&data_table, hash_table_value);
    value_id++;

    if(token_type == IDENTIFIER){
        identifier_bst_add(chunk, "nil");
    }

}
