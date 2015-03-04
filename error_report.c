#include <stdio.h>
#include <stdlib.h>

#include "error_report.h"

const char* error_token_types[] = {
    "IDENTIFIER", "STRING", "NUMBER",
    "=",  "+", "-", "*", "/",
    "<", ">", "<=", ">=", "==", "!=",
    "var", "if", "when", "(", ")", "{", "}", "\\n"
};

void show_error_and_exit(int code, int ln){
    switch(code){
    case SOURCE_NOT_PROVIDED:
        printf("ERROR %d: Source file not given", code);
        break;
    case SOURCE_NOT_FOUND:
        printf("ERROR %d: No such file found", code);
        break;
    case DATA_TABLE_OUT_OF_BOUND:
        printf("ERROR %d: Data table index out of range!", code);
        break;

    case INTERPRETER_ERROR_ALREADY_DEFIEND:
        printf("ERROR %d: Cannot redeclare variable at line %d!", code, ln);
        break;

    default:
        printf("ERROR %d: Undefined Error!", code);
        break;
    }

    printf("\n");
    exit(1);
}

void show_parser_error_and_exit(int code, int ln, TOKEN_TYPE expected, TOKEN_TYPE found){
    switch(code){
        case PARSER_ERROR_UNEXPECTED:
            printf("ERROR %d: Unexpected '%s' at line %d!", code, error_token_types[found], ln);
            break;
        case PARSER_ERROR_EXPECTED:
            printf("ERROR %d: Expected '%s' but found '%s' at line %d!", code, error_token_types[expected], error_token_types[found], ln);
            break;
    }
    printf("\n");
    exit(1);
}
