#include <ctype.h>
#include <string.h>
#include "fsm.h"

/*--------- FINITE STATE MACHINE FOR IDENTIFIERS ------------*/
int fsm_identifier_check(char* chunk, int len){
    int flag = 0;
    int x = 0, state = 0;
    while(x < len){
        char c = chunk[x];
        switch(state){
        case 0:
            if(isalpha(c) || c == '_'){
                state = 1;
                flag = 1;
            }else{
                state = 2;
            }
            break;

        case 1:
            if(isalnum(c) || c == '_'){
                state = 1;
                flag = 1;
            }else{
                state = 2;
            }
            break;
        case 2:
        default:
            flag = 0;
            break;
        }
        x++;
        if(flag == 0) break;
    }

    return flag;
}

/*--------- FINITE STATE MACHINE FOR NUMBERS ------------*/
int fsm_number_check(char* chunk, int len){
    int flag = 0;
    int x = 0, state = 0;

    while(x < len){
        char c = chunk[x];
        switch(state){
        case 0:
            if(isdigit(c)){
                state = 1;
                flag = 1;
            }else{
                state = 4;
                flag = 0;
            }
            break;
        case 1:
            if(isdigit(c)){
                state = 1;
                flag = 1;
            }else if(c == '.'){
                state = 2;
                flag = 0;
            }else{
                state = 4;
                flag = 0;
            }
            break;
        case 2:
            if(isdigit(c)){
                state = 3;
                flag = 1;
            }else {
                state = 4;
                flag = 0;
            }
            break;
        case 3:
            if(isdigit(c)){
                state = 3;
                flag = 1;
            }else{
                state = 4;
                flag = 0;
            }

        case 4:
        default:
            state = 4;
            flag = 0;
        }
        x++;
    }

    return flag;

}
