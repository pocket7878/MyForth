#include <stdio.h>
#include "prog.h"
#include "calc.h"
#include "stack.h"


void plus(void)
{
	char a, b, c;
	a = pop();
	b = pop();
	c = a + b;
	push(c);
}

void minus(void)
{
	char a, b, c;
	a = pop();
	b = pop();
	c = a - b;
	push(c);
}

void times(void)
{
	char a, b , c;
	a = pop();
	b = pop();
	c = a * b;
	push(c);
}

void mod(void)
{
	char a, b, c;
	a = pop();
	b = pop();
	c = a % b;
	push(c);
}

void rem(void)
{
	char a, b, c;
	a = pop();
	b = pop();
	c = a / b;
	push(c);
}

void rem_mod(void)
{
	char a, b, rem, mod;
	a = pop();
	b = pop();
	rem = a / b;
	mod = a % b;
	push(rem);
	push(mod);
}

void less_than(void)
{
	char a, b;
	a = pop();
	b = pop();
	if(a>b) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}

void greater_than(void)
{
	char a, b;
	a = pop();
	b = pop();
	if(a<b) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}

void less_or_equal(void)
{
	char a, b;
	a = pop();
	b = pop();
	if(a>=b) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}

void greater_or_equal(void)
{
	char a, b;
	a = pop();
	b = pop();
	if(a<=b) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}

// <>
void not_equal(void)
{
	char a, b;
	a = pop();
	b = pop();
	if(a!=b) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}
// =
void equals(void)
{
	char a, b;
	a = pop();
	b = pop();
	if(a==b) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}
// 0<
void zero_less_than(void)
{
	char a;
	a = pop();
	if(a < 0) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}
// 0<=
void zero_less_or_equal(void)
{
	char a;
	a = pop();
	if(a <= 0) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}
// 0<>
void zero_not_equals(void)
{
	char a;
	a = pop();
	if(a != 0) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}
// 0=
void zero_equals(void)
{
	char a;
	a = pop();
	if(a == 0) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}
// 0> 
void zero_greater_than(void)
{
	char a;
	a = pop();
	if(a > 0) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}
// 0>=
void zero_greater_or_equal(void)
{
	char a;
	a = pop();
	if(a >= 0) {
		push(TRUE);
	}
	else {
		push(FALSE);
	}
}
