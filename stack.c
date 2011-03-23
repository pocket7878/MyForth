#include <stdio.h>
#include "stack.h"

//Stack 
int pos = sizeof(stack)/sizeof(char) -1;

void push(char val)
{
	stack[pos] = val;
	pos--;
}

char pop(void) 
{
	pos++;
	return stack[pos];
}

void print(void)
{
	char a;
	a = pop();
	printf("%d\n", a);
}

void dup(void)
{
	char a;
	a = pop();
	push(a);
	push(a);
}

void swap(void)
{
	char a, b;
	a = pop();
	b = pop();
	push(a);
	push(b);
}
