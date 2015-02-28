#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "grammer.h"
#include "global_things.h"

FILE *file_input_handler;


void read_file(char* file_name);

void tokenizer();
void add_token(TOKEN_TYPE token_type);
void add_value(TOKEN_TYPE);
void add_token_chunk();
#endif // LEXER_H_INCLUDED
