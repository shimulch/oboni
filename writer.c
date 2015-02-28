#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "writer.h"
#include "grammer.h"
#include "global_things.h"
char syntax_tree_stack[10000]= {};
const char* token_types[] = {
    "IDENTIFIER", "STRING", "NUMBER",
    "ASSIGNMENT_OPERATOR",  "ADDITION_OPERATOR", "SUBSTRUCTION_OPERATOR", "MULTIPLICATION_OPERATOR", "DIVISION_OPERATOR",
    "LT_OPERATOR", "BT_OPERATOR", "LEQ_OPERATOR", "BEQ_OPERATOR", "EQ_OPERATOR", "NE_OPERATOR",
    "VAR", "IF", "WHEN", "LP", "RP", "LCB", "RCB", "NEWLINE"
};

void write_token_array(){
    file_writer_handler = fopen(token_array_file_name, "w");
    int i = 0;
    for(; i<token_array.length; i++){
        if(token_array.ARRAY[i].token_type == NEWLINE){
            fprintf(file_writer_handler, "%s\n\n", token_types[token_array.ARRAY[i].token_type]);
        }
        else
            fprintf(file_writer_handler, "%s ", token_types[token_array.ARRAY[i].token_type]);
    }
    fclose(file_writer_handler);
}


void write_syntax_tree(char* message){
    strcat(syntax_tree_stack, message);
    file_writer_handler = fopen(syntax_tree_file_name, "a");
    fprintf(file_writer_handler, "%s\n", syntax_tree_stack);
    fclose(file_writer_handler);
}
