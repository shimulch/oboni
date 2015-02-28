#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED
#include <stdio.h>
FILE* file_writer_handler;
char syntax_tree_file_name[100];
char token_array_file_name[100];
void write_token_array();
void write_syntax_tree(char* message);

#endif // WRITER_H_INCLUDED
