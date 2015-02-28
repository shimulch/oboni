#ifndef FSM_H_INCLUDED
#define FSM_H_INCLUDED

int fsm_identifier_check(char* chunk, int len);
int fsm_number_check(char* chunk, int len);
int fsm_string_check(char* chunk, int len);

#endif // FSM_H_INCLUDED
