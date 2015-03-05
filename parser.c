#include "parser.h"
#include "global_things.h"
#include "error_report.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int current_token_index = 0, line_number = 1;
TOKEN current_token;
TOKEN_TYPE current_token_type;
int CURRENT_STATE = STATE_EXPRESSION;

int open_cb = 0, open_p = 0;


/*------------- CREATE ABSTRACT SYNTAX TREE ----------------*/
void parse(){
    global_current_scope = 0;
    get_next_token();

    ast_root = expression();

}


/*-------------- GET NEXT TOKEN ----------------------------*/
void get_next_token(){
    current_token = token_array_get(&token_array, current_token_index);
    current_token_type= current_token.token_type;
    current_token_index++;
}

/*--------------- IS LAST TOKEN ----------------------------*/
int is_last_token(){
    if(current_token.token_id == token_array.length - 1) return 1;
    return 0;
}


/*
 * RULE: EXPRESSION -> STATEMENT EXPRESSION'
 *                   | CONTROLFLOW EXPRESSION'
 *                   | EPSILON
 */
AST_NODE* expression(){


    // if statement
    if(current_token_type == VAR || current_token_type == ASSIGNMENT_OPERATOR || current_token_type == SHOW){
        AST_NODE* exp = create_ast_node(EXPRESSION);
        exp->childs[0] = statement();
        exp->childs[1] = expression_prime();
        return exp;
    }
    // if a control flow
    else if(current_token_type == IF || current_token_type == WHEN){
        AST_NODE* exp = create_ast_node(EXPRESSION);
        exp->childs[0] = control_flow();
        exp->childs[1] = expression_prime();
        return exp;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, VAR, current_token_type);
    }
    return NULL;
}


/*
 * RULE: EXPRESSION' -> STATEMENT NEWLINE EXPRESSION
 *                    | CONTROLFLOW NEWLINE EXPRESSION
 *                    | STATEMENT
 *                    | CONTROLFLOW
 *                    | EPSILON
 */

AST_NODE* expression_prime(){
    // write me

    //printf("%d  %d\n",current_token.token_id, open_cb);

    if(current_token_type == NEWLINE && !is_last_token()){
        get_next_token();
        line_number++;
        AST_NODE* exp_p = create_ast_node(EXPRESSION_PRIME);
        if(current_token_type == RCB && open_cb > 0){
            free(exp_p);
            return NULL;
        }
        exp_p->childs[0] = expression();
        return exp_p;
    }
    else if(current_token_type == NEWLINE && is_last_token()){

    }
    else {
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, NEWLINE, current_token_type);
    }

    return NULL;
}

/*
 * RULE: STATEMENT  -> var identifier
 *                   | assignment_operator identifier TERM
 */
AST_NODE* statement(){


    if(current_token_type == VAR){
        AST_NODE* stmnt = create_ast_node(STATEMENT);
        stmnt->childs[0] = var_t();
        stmnt->childs[1] = identifier_t();
        return stmnt;
    }
    // if ASSIGNMENT
    else if(current_token_type == ASSIGNMENT_OPERATOR){

        AST_NODE* stmnt = create_ast_node(STATEMENT);
        stmnt->childs[0] = operator_t();
        stmnt->childs[1] = identifier_t();
        stmnt->childs[2] = term();
        return stmnt;
    }

    // if SHOW
    else if(current_token_type == SHOW){

        AST_NODE* stmnt = create_ast_node(SHOW_METHOD);
        get_next_token();
        stmnt->childs[1] = term();
        return stmnt;
    }
    else {
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, VAR, current_token_type);
    }
    return NULL;
}

/*
 * RULE: CONTROLFLOW -> if lp EVALUATION rp BLOCK
 *                    | when lp EVALUATION rp BLOCK
 */
AST_NODE* control_flow(){
    // write me
    // if IF found
    if(current_token_type == IF){
        AST_NODE* ctrl_flow = create_ast_node(CONTROL_FLOW);
        ctrl_flow->childs[0] = if_t();
        lp_t();

        ctrl_flow->childs[1] = evaluation();
        rp_t();

        ctrl_flow->childs[2] = block();
        return ctrl_flow;
    }
    // if WHEN found
    else if(current_token_type == WHEN){
        AST_NODE* ctrl_flow = create_ast_node(CONTROL_FLOW);
        ctrl_flow->childs[0] = when_t();
        lp_t();
        ctrl_flow->childs[1] = evaluation();
        rp_t();
        ctrl_flow->childs[2] = block();

        return ctrl_flow;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, IF, current_token_type);
    }
    return NULL;
}

/*
 * RULE: BLOCK -> lcb EXPRESSION' rcb EXPRESSION'
 */
AST_NODE* block(){

    if(current_token_type == LCB){
        lcb_t();
        AST_NODE* blck = create_ast_node(BLOCK);

        blck->childs[0] = expression_prime();

        rcb_t();

        return blck;
    }else {
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, LCB, current_token_type);
    }
    return NULL;
}

/*-------------- IDENTIFIER -------------------------------*/


/*
 * RULE: TERM  -> identifier
 *              | number
 *              | lp EVALUATION rp
 */
AST_NODE* term(){
    // write me

    if(current_token_type == IDENTIFIER){
        return identifier_t();
    }else if(current_token_type == NUMBER){
        return number_t();
    }
    else if(current_token_type == STRING){
        return string_t();
    }
    else if(current_token_type == LP){
        lp_t();
        AST_NODE* eval = evaluation();
        rp_t();
        return eval;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, IDENTIFIER, current_token_type);
    }

    return NULL;
}

/*
 * RULE: EVALUATION  -> operator TERM TERM
 */
AST_NODE* evaluation(){
    // write me
    AST_NODE* eval = create_ast_node(EVALUATION);
    eval->childs[0] = operator_t();
    eval->childs[1] = term();
    eval->childs[2] = term();
    return eval;
}





/*------------- TERMINALS ----------------*/

void lp_t(){
    if(current_token_type == LP){

        open_p++;
        get_next_token();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, LP, current_token_type);
    }
}

void rp_t(){
    if(current_token_type == RP){
        open_p--;

        get_next_token();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, RP, current_token_type);
    }
}

void lcb_t(){
    if(current_token_type == LCB){
        open_cb++;

        get_next_token();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, LCB, current_token_type);
    }
}

void rcb_t(){
    if(current_token_type == RCB){
        open_cb--;

        get_next_token();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, RCB, current_token_type);
    }
}

AST_NODE* operator_t(){
    switch(current_token_type){
    case ADDITION_OPERATOR:
    case MULTIPLICATION_OPERATOR:
    case DIVISION_OPERATOR:
    case LT_OPERATOR:
    case BT_OPERATOR:
    case LEQ_OPERATOR:
    case BEQ_OPERATOR:
    case EQ_OPERATOR:
    case NE_OPERATOR:
    case ASSIGNMENT_OPERATOR:
        break;
    default:
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, ADDITION_OPERATOR, current_token_type);
        break;
    }
    AST_NODE* ast_node = create_ast_node(MAIN_TOKEN);
    get_next_token();
    return ast_node;
}

AST_NODE* identifier_t(){
    // write me

    if(current_token_type == IDENTIFIER){
        // get hash table data
        AST_NODE* ast_node = create_ast_node(MAIN_TOKEN);

        get_next_token();
        return ast_node;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, IDENTIFIER, current_token_type);
    }
    return NULL;
}

AST_NODE* string_t(){
    // write me

    if(current_token_type == STRING){
        // get hash table data
        AST_NODE* ast_node = create_ast_node(MAIN_TOKEN);

        get_next_token();
        return ast_node;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, STRING, current_token_type);
    }
    return NULL;
}

AST_NODE* var_t(){
    if(current_token_type == VAR){
        AST_NODE* ast_node = create_ast_node(MAIN_TOKEN);
        get_next_token();
        return ast_node;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, VAR, current_token_type);
    }
    return NULL;
}

AST_NODE* if_t(){
    if(current_token_type == IF){
        AST_NODE* ast_node = create_ast_node(MAIN_TOKEN);
        get_next_token();
        return ast_node;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, IF, current_token_type);
    }
    return NULL;
}


AST_NODE* when_t(){
    if(current_token_type == WHEN){
        AST_NODE* ast_node = create_ast_node(MAIN_TOKEN);

        get_next_token();

        return ast_node;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, WHEN, current_token_type);
    }
    return NULL;
}

AST_NODE* number_t(){
    if(current_token_type == NUMBER){

        AST_NODE* ast_node = create_ast_node(MAIN_TOKEN);

        get_next_token();

        return ast_node;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, NUMBER, current_token_type);
    }

    return NULL;
}

AST_NODE* create_ast_node(AST_NODE_TYPE type){
    AST_NODE* newNode = calloc(1, sizeof(AST_NODE));
    newNode->node_type = type;
    if(type == MAIN_TOKEN){
        newNode->token = current_token;
    }
    int i = 0;
    for(;i<10;i++)
        newNode->childs[i] = NULL;
    return newNode;
}
