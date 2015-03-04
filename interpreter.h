#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED
#include "grammer.h"
#include "global_things.h"

void interpret();
char* interpreter(AST_NODE* node);
char* get_identifier_value(char* identifier);
char* get_number_value(char* number);

void declare_identifier(TOKEN token, int line_number);
void assign_identifier(TOKEN token, char* value, int line_number);

char* interpret_term(AST_NODE* t);

char* calculate(TOKEN_TYPE t_type, char* a, char* b);
char* custom_itoa(long long val, int base);

void show(char* thing, int ln);
#endif // INTERPRETER_H_INCLUDED
