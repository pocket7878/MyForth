#ifndef _CONTROL_H_
#define _CONTROL_H_

void bye(void);
//Stack for if then else
int if_stack_size;
int* if_stack;
int if_pos;

void push_if_stack(int);
int pop_if_stack(void);

#endif
