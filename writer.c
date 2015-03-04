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
    "VAR", "IF", "WHEN", "SHOW", "LP", "RP", "LCB", "RCB", "NEWLINE"
};
const char* ast_node_type[] = {
    "EXPRESSION", "EXPRESSION_PRIME", "STATEMENT", "TERM", "CONTROL_FLOW", "EVALUATION", "MAIN_TOKEN", "BLOCK", "SHOW_METHOD"
};
void write_token_array(){
    if(debug){
    file_writer_handler = fopen(token_array_file_name, "w");
    int i = 0;
    for(; i<token_array.length; i++){
        if(token_array.ARRAY[i].token_type == NEWLINE){
            fprintf(file_writer_handler, "%s\n\n", token_types[token_array.ARRAY[i].token_type]);
        }
        else
            fprintf(file_writer_handler, "%d->%s ", i, token_types[token_array.ARRAY[i].token_type]);
    }
    fclose(file_writer_handler);
    }
}


void write_syntax_tree(AST_NODE* current, int level){
    if(debug){
        file_writer_handler = fopen(syntax_tree_file_name, "a");

        syntax_tree_writer(current, level);
        fclose(file_writer_handler);
    }
}

void syntax_tree_writer(AST_NODE* current, int level){

        int i =0;
        for(; i<level; i++)
            fprintf(file_writer_handler, "    ");

        if(current->node_type == MAIN_TOKEN){
            fprintf(file_writer_handler, "%s\n", token_types[current->token.token_type]);
            return;
        }
        fprintf(file_writer_handler, "%s:\n", ast_node_type[current->node_type]);


        for(i = 0;i<10; i++){
            if(current->childs[i]){
                syntax_tree_writer(current->childs[i], level+1);
            }
        }
        for(i = 0; i<level; i++)
            fprintf(file_writer_handler, "    ");
        fprintf(file_writer_handler, "END %s\n", ast_node_type[current->node_type]);
}
