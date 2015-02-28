#ifndef ERROR_REPORT_H_INCLUDED
#define ERROR_REPORT_H_INCLUDED

#include "global_things.h"

/*----------- defining error codes --------------*/
#define DATA_TABLE_OUT_OF_BOUND 101

#define SOURCE_NOT_PROVIDED 201
#define SOURCE_NOT_FOUND 202

#define PARSER_ERROR 301
#define PARSER_ERROR_UNEXPECTED 302
#define PARSER_ERROR_EXPECTED 303

void show_error_and_exit(int code, int ln);


void show_parser_error_and_exit(int code, int ln, TOKEN_TYPE expected, TOKEN_TYPE found);

#endif // ERROR_REPORT_H_INCLUDED
