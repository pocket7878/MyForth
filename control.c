#include <stdio.h>
#include <stdlib.h>
#include "control.h"

void bye(void)
{
	exit(0);
}

void push_if_stack(int adrs)
{
	printf("PUSH IF STACK: %d\n",adrs);
	if_pos--;
	if_stack[if_pos] = adrs;
}

int pop_if_stack(void)
{
	int ret_val;
	ret_val = if_stack[if_pos++]; 
	printf("POP IF STACK: %d\n",ret_val);
	return ret_val;
}
