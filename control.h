#ifndef _CONTROL_H_
#define _CONTROL_H_

void bye(void);
//Stack for if then else
char if_stack[100];
int if_pos;
void push_if_stack(char);
char pop_if_stack(void);

#endif
