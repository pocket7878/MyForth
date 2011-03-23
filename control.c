#include <stdio.h>
#include <stdlib.h>
#include "prog.h"
#include "control.h"

int if_stack_size = 0;
int if_pos = 0;

void bye(void)
{
	//free malloced memory
	free(if_stack);
	free(prog);
	exit(0);
}

void push_if_stack(int adrs)
{	
	//初回よびだしまではifstackは確保しない
	if(if_stack_size == 0) {
		//malloc stack
		if_stack = (int *)malloc(sizeof(int) * 100);
		if(if_stack == NULL) {
			fprintf(stderr,"Malloc Error!!\n");
			bye();
		}
		else {
			if_stack_size = 100;
			if_pos = 0;
		}
	}
	else if(if_pos == if_stack_size) {
		if_stack = (int *)realloc(if_stack,sizeof(int) * (if_stack_size + 10));
		if(if_stack == NULL) {
			fprintf(stderr,"Realloc Error!!\n");
			bye();
		}
		else {
			if_stack_size += 10;
		}
	}
	if_pos++;
	if_stack[if_pos] = adrs;
}

int pop_if_stack(void)
{
	int ret_val;
	ret_val = if_stack[if_pos--]; 
	return ret_val;
}
