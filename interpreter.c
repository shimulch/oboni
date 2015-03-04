#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "interpreter.h"
#include "global_things.h"
#include "error_report.h"

void interpret(){
    interpreter(ast_root);
}

char* interpreter(AST_NODE* node){
    char* term_value;
    TOKEN token;
    int helper;
    switch(node->node_type){


    case EXPRESSION:
        if(node->childs[0])
            interpreter(node->childs[0]);
        if(node->childs[1])
            interpreter(node->childs[1]);
        break;


    case EXPRESSION_PRIME:
        if(node->childs[0])
            interpreter(node->childs[0]);
        break;


    case STATEMENT:
        switch(node->childs[0]->token.token_type){
        case VAR:
            declare_identifier(node->childs[1]->token, 0);
            break;
        case ASSIGNMENT_OPERATOR:
            assign_identifier(node->childs[1]->token, interpreter(node->childs[2]),  0);
            break;
        default:
            break;
        }
        break;

    case TERM:
        if(node->childs[0]->node_type == EVALUATION){
            term_value = interpreter(node->childs[0]);
        }
        else{
            token = node->childs[0]->token;
            if(token.token_type == IDENTIFIER){
                term_value = get_identifier_value(token.value);
            }else{
                term_value = token.value;
            }
        }
        return term_value;

    case EVALUATION:
        return calculate(node->childs[0]->token.token_type, interpreter(node->childs[1]), interpreter(node->childs[2]));

    case CONTROL_FLOW:

        token = node->childs[0]->token;
        if(token.token_type == IF){
            term_value = interpreter(node->childs[1]);
            helper = strcmp(term_value, "0");

            if(helper > 0){
                interpreter(node->childs[2]);
            }
        }else if(token.token_type == WHEN){

            term_value = interpreter(node->childs[1]);
            helper = strcmp(term_value, "0");
            while(helper > 0){
                interpreter(node->childs[2]);
                term_value = interpreter(node->childs[1]);

                helper = strcmp(term_value, "0");
            }
        }

        break;

    case MAIN_TOKEN:
        if(node->token.token_type == IDENTIFIER)
            return get_identifier_value(node->token.value);
        else{
            return node->token.value;
        }

        break;
    case BLOCK:
        interpreter(node->childs[0]);
        break;
    case SHOW_METHOD:
        show(interpreter(node->childs[1]), 0);
        break;
    }

    return "";
}



/*----------- VARIABLE DECLARATION ---------------*/
void declare_identifier(TOKEN token, int line_number){

    char* current_value = get_identifier_value(token.value);
    if(current_value){
        if(strcmp(current_value, "undefined") != 0){
            show_error_and_exit(INTERPRETER_ERROR_ALREADY_DEFIEND, line_number);
        }
    }

    identifier_bst_add(token.value, "null");
}

/*----------- VARIABLE ASSIGNMENT ---------------*/
void assign_identifier(TOKEN token, char* value, int line_number) {
    //puts(current_value);
    //puts(value);
    //return;
    char* current_value = get_identifier_value(token.value);
    if(current_value){
        if(strcmp(current_value, "undefined") == 0){
            show_error_and_exit(INTERPRETER_ERROR_ALREADY_DEFIEND, line_number);
        }
    }
    identifier_bst_add(token.value, value);
}


/*----------- CALCULATION ---------------*/
char* calculate(TOKEN_TYPE t_type, char* a, char* b){
    long long number_a = atoll(a);
    long long number_b = atoll(b);
    char *ans = NULL;
    switch(t_type){
    case ADDITION_OPERATOR:
        number_a += number_b;
        break;
    case SUBSTRUCTION_OPERATOR:
        number_a -= number_b;
        break;
    case DIVISION_OPERATOR:
        number_a /= number_b;
        break;
    case MULTIPLICATION_OPERATOR:
        number_a *= number_b;
        break;

    case LT_OPERATOR:
        number_a = (number_a < number_b)?1:0;
        break;
    case BT_OPERATOR:
        number_a = (number_a > number_b)?1:0;
        break;
    case EQ_OPERATOR:
        number_a = (number_a == number_b)?1:0;
        break;
    case LEQ_OPERATOR:
        number_a = (number_a <= number_b)?1:0;
        break;
    case BEQ_OPERATOR:
        number_a = (number_a <= number_b)?1:0;
        break;
    case NE_OPERATOR:
        number_a = (number_a != number_b)?1:0;
        break;
    default:
        break;
    }


    ans = custom_itoa(number_a, 10);
    if(strlen(ans) == 0){
        ans = "0";
    }
    return ans;
}

/*----------- GET VALUE FROM VARIABLE ---------------*/
char* get_identifier_value(char* identifier){
    I_BST* value_of_id = identifier_bst_get(identifier);
    if(value_of_id){
        return value_of_id->value;
    }else{
        return "undefined";
    }
}

/*----------- CALCULATION HELPER ---------------*/
char* custom_itoa(long long val, int base){

    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i+1];

}

void show(char* thing, int ln){

    if(thing)
        printf("%s",thing);
    else
        show_error_and_exit(500, ln);
}
