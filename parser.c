#include "parser.h"
#include "global_things.h"
#include "error_report.h"
#include "writer.h"
#include <ctype.h>
#include <string.h>

int current_token_index = 0, line_number = 1;
TOKEN current_token;
TOKEN_TYPE current_token_type;
int CURRENT_STATE = STATE_EXPRESSION;

int open_cb = 0, open_p = 0;

/*------------- CREATE ABSTRACT SYNTAX TREE ----------------*/
void parse(){
    get_next_token();
    expression();
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
void expression(){
    // write me
    write_syntax_tree("E ");
    //printf("%d %d\n", current_token_type, open_cb);
    if(current_token_type == RCB && open_cb > 0){
            return;
    }
    // if statement
    else if(current_token_type == VAR || current_token_type == ASSIGNMENT_OPERATOR){
        statement();
        expression_prime();
    }
    // if a control flow
    else if(current_token_type == IF || current_token_type == WHEN){
        control_flow();
        expression_prime();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, VAR, current_token_type);
    }
}


/*
 * RULE: EXPRESSION' -> STATEMENT NEWLINE EXPRESSION
 *                   | CONTROLFLOW NEWLINE EXPRESSION
 *                   | STATEMENT
 *                   | CONTROLFLOW
 *                   | EPSILON
 */

void expression_prime(){
    // write me
    write_syntax_tree("E' ");
    //printf("%d  %d\n",current_token.token_id, open_cb);


    if(current_token_type == NEWLINE && !is_last_token()){
        get_next_token();
        line_number++;
        expression();
    }
    else if(current_token_type == NEWLINE && is_last_token()){
        write_syntax_tree("END ");
    }
    else {
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, NEWLINE, current_token_type);
    }
}

/*
 * RULE: STATEMENT  -> var identifier
 *                   | assignment_operator identifier TERM
 */
void statement(){

    // write me
    write_syntax_tree("S ");

    // if VARIABLE DECLARATION
    if(current_token_type == VAR){
        var_t();
        identifier_t();
    }
    // if ASSIGNMENT
    else if(current_token_type == ASSIGNMENT_OPERATOR){
        write_syntax_tree("= ");
        get_next_token();
        identifier_t();
        term();
    }else {
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, VAR, current_token_type);
    }
}

/*
 * RULE: CONTROLFLOW -> if lp EVALUATION rp BLOCK
 *                    | when lp EVALUATION rp BLOCK
 */
void control_flow(){
    // write me
    write_syntax_tree("CF ");
    // if IF found
    if(current_token_type == IF){
        if_t();
        lp_t();
        evaluation();
        rp_t();
        block();
    }
    // if WHEN found
    else if(current_token_type == WHEN){
        when_t();
        lp_t();
        evaluation();
        rp_t();
        block();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, IF, current_token_type);
    }
}

/*
 * RULE: BLOCK -> lcb EXPRESSION' rcb EXPRESSION'
 */
void block(){
    write_syntax_tree("BLC ");
    if(current_token_type == LCB){
        lcb_t();
        expression_prime();
        rcb_t();
        expression_prime();
    }else {
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, LCB, current_token_type);
    }

}

/*-------------- IDENTIFIER -------------------------------*/


/*
 * RULE: TERM  -> identifier
 *              | number
 *              | lp EVALUATION rp
 */
void term(){
    // write me
    write_syntax_tree("TERM ");

    if(current_token_type == IDENTIFIER){
        identifier_t();
    }else if(current_token_type == NUMBER){
        number_t();
    }else if(current_token_type == LP){
        lp_t();
        evaluation();
        rp_t();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, IDENTIFIER, current_token_type);
    }
}

/*
 * RULE: EVALUATION  -> operator TERM TERM
 */
void evaluation(){
    // write me
    write_syntax_tree("EVAL ");
    operator_t();
    term();
    term();
}





/*------------- TERMINALS ----------------*/

void lp_t(){
    if(current_token_type == LP){
        write_syntax_tree("( ");
        open_p++;
        get_next_token();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, LP, current_token_type);
    }
}

void rp_t(){
    if(current_token_type == RP){
        open_p--;
        write_syntax_tree(") ");
        get_next_token();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, RP, current_token_type);
    }
}

void lcb_t(){
    if(current_token_type == LCB){
        open_cb++;
        write_syntax_tree("{ ");
        get_next_token();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, LCB, current_token_type);
    }
}

void rcb_t(){
    if(current_token_type == RCB){
        open_cb--;
        write_syntax_tree("} ");
        get_next_token();
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, RCB, current_token_type);
    }
}

void operator_t(){
    write_syntax_tree("op ");
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
        get_next_token();
        break;
    default:
        show_parser_error_and_exit(PARSER_ERROR_UNEXPECTED, line_number, ADDITION_OPERATOR, current_token_type);
        break;
    }
}

void identifier_t(){
    // write me
    write_syntax_tree("id ");

    if(current_token_type == IDENTIFIER){
        // get hash table data
        HASH_TABLE_DATA hash_table_value = hash_table_get(&data_table, current_token.value_id);
        char identifier[20];
        strcpy(identifier, hash_table_value.value);

        I_BST* value_of_id = identifier_bst_get(identifier);
        strcat(identifier, " ");
        if(value_of_id != NULL){
            strcat(identifier, "= ");
            strcat(identifier, value_of_id->value);
            strcat(identifier, " ");
        }

        write_syntax_tree(identifier);
        get_next_token();
        return;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, IDENTIFIER, current_token_type);
    }
}

void var_t(){
    write_syntax_tree("var ");
    if(current_token_type == VAR){
        get_next_token();
        return;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, VAR, current_token_type);
    }
}

void if_t(){
    write_syntax_tree("if ");
    if(current_token_type == IF){
        get_next_token();
        return;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, IF, current_token_type);
    }
}


void when_t(){
    write_syntax_tree("when ");
    if(current_token_type == WHEN){
        get_next_token();
        return;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, WHEN, current_token_type);
    }
}

void number_t(){
    write_syntax_tree("num ");
    if(current_token_type == NUMBER){
        // get hash table data
        HASH_TABLE_DATA hash_table_value = hash_table_get(&data_table, current_token.value_id);
        char number[20];
        strcpy(number, hash_table_value.value);
        strcat(number, " ");
        write_syntax_tree(number);
        get_next_token();
        return;
    }else{
        show_parser_error_and_exit(PARSER_ERROR_EXPECTED, line_number, NUMBER, current_token_type);
    }
}
