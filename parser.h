#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "global_things.h"

#define STATE_EXPRESSION 1
#define STATE_STATEMENT 2
#define STATE_CONTROLFLOW 3
#define STATE_TERM 4
#define STATE_EVALUATION 5
#define STATE_OPERATOR 6
#define STATE_BLOCK 7

#define STATE_ERROR 101

void parse();

void get_next_token();
int is_last_token();
AST_NODE* create_ast_node(AST_NODE_TYPE type);
/*---------------- TERMINALS -------------*/
AST_NODE* identifier_t();
AST_NODE* string_t();
AST_NODE* operator_t();
AST_NODE* number_t();
void lp_t();
void rp_t();
void lcb_t();
void rcb_t();
AST_NODE* var_t();
AST_NODE* if_t();
AST_NODE* when_t();
AST_NODE* assignment_operator_t();
/*---------------- NON TERMINALS -------------*/
AST_NODE* expression();
AST_NODE* expression_prime();
AST_NODE* statement();
AST_NODE* evaluation();
AST_NODE* control_flow();
AST_NODE* block();
AST_NODE* term();

#endif // PARSER_H_INCLUDED
