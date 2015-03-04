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

    read_file(argv[1]);

    debug = 0;
    //write token array

    printf( "Content-type: text/html\n\n");

    strcpy(token_array_file_name, argv[1]);
    strcpy(syntax_tree_file_name, argv[1]);
    strcat(token_array_file_name, ".tokens.txt");
    strcat(syntax_tree_file_name, ".ast.txt");
    remove( syntax_tree_file_name );
    write_token_array();
    parse();
    write_syntax_tree(ast_root, 0);
    interpret();
    return 0;
}
