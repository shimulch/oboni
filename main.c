#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*----- LANGUAGE LIBRARIES ------*/
#include "global_things.h"
#include "grammer.h"
#include "error_report.h"
#include "lexer.h"
#include "writer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argvc, char* argv[])
{
    //printf("Oboni version 0.0.1\n\n");

    if(argvc < 2) show_error_and_exit(SOURCE_NOT_PROVIDED, 0);

    if(argvc >= 3){
        if(strcmp(argv[2], "-D")){
            debug = 1;
        }else{
            debug = 0;
        }
    }


    read_file(argv[1]);



    //write token array
    if(debug){
        strcpy(token_array_file_name, argv[1]);
        strcpy(syntax_tree_file_name, argv[1]);
        strcat(token_array_file_name, ".tokens.txt");
        strcat(syntax_tree_file_name, ".ast.txt");
        remove( syntax_tree_file_name );
        write_token_array();
    }
    parse();
    free_token_array(&token_array);
    if(debug){
        write_syntax_tree(ast_root, 0);
    }
    interpret();
    return 0;
}
