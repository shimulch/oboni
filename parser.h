#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

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

/*---------------- TERMINALS -------------*/
void identifier_t();
void operator_t();
void number_t();
void lp_t();
void rp_t();
void lcb_t();
void rcb_t();
void var_t();
void if_t();
void when_t();
void assignment_operator_t();
/*---------------- NON TERMINALS -------------*/
void expression();
void expression_prime();
void statement();
void evaluation();
void control_flow();
void block();
void term();


#endif // PARSER_H_INCLUDED
