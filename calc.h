#ifndef _CALC_H_
#define _CALC_H_

//四則演算
void plus(void);
void minus(void);
void times(void);
void mod(void);
void rem(void);

//比較関数
// <
void less_than(void);
// >
void greater_than(void);
// <=
void less_or_equal(void);
// >=
void greater_or_equal(void);
// <>
void not_equal(void);
// =
void equals(void);
// 0<
void zero_less_than(void);
// 0<=
void zero_less_or_equal(void);
// 0<>
void zero_not_equals(void);
// 0=
void zero_equals(void);
// 0> 
void zero_greater_than(void);
// 0>=
void zero_greater_or_equal(void);

#endif
