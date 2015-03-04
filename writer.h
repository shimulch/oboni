#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED
#include "global_things.h"
#include <stdio.h>
FILE* file_writer_handler;
char syntax_tree_file_name[100];
char token_array_file_name[100];
void write_token_array();
void write_syntax_tree(AST_NODE* current, int level);
void syntax_tree_writer(AST_NODE* current, int level);
int debug;
#endif // WRITER_H_INCLUDED
