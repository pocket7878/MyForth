#include <stdio.h>
#include "eval.h"
#include "prog.h"
#include "calc.h"
#include "stack.h"
#include "read.h"
#include "control.h"

enum ePROG eprog;

int base_prog_cnt = 0;
int function_state = 0;
void eval_prog(void)
{

	//int j;
	if(mode == LOAD) {
		prog_cnt = 0;
	}
	//for(j = 0; j < prog_stack_size && !(prog[j - 1] != FCALL && prog[j + 1] == FEND); j++) {
	//	printf("Program cnt: %d word: %d\n",j,prog[j]);
	//}
	while(prog[prog_cnt] != FEND) {
		if(function_state == 0) {
			//printf("Top Level\n");
			switch(prog[prog_cnt]) {
				case FPUSH:
					//PUSH
					push(prog[prog_cnt + 1]);
					prog_cnt += 2;
					break;
				case FPLUS:
					//PLUS
					plus();
					prog_cnt++;
					break;
				case FMINUS:
					minus();
					prog_cnt++;
					break;
				case FTIMES:
					times();
					prog_cnt++;
					break;
				case FMOD:
					mod();
					prog_cnt++;
					break;
				case FREM:
					rem();
					prog_cnt++;
					break;
				case FIF:
					if(pop() != FALSE) {
						prog_cnt += 2;
					}
					else {
						prog_cnt = prog[prog_cnt + 1];
					}
					break;
				case FELSE:
					prog_cnt = prog[prog_cnt + 1];
					break;
				case FTHEN:
					prog_cnt++;
					break;
				case FLESSTHAN:
					less_than();
					prog_cnt++;
					break;
				case FLESSOREQUAL:
					less_or_equal();
					prog_cnt++;
					break;
				case FNOTEQUALS:
					not_equal();
					prog_cnt++;
					break;
				case FEQUALS:
					equals();
					prog_cnt++;
					break;
				case FGREATERTHAN:
					greater_than();
					prog_cnt++;
					break;
				case FGREATEROREQUAL:
					greater_or_equal();
					prog_cnt++;
					break;
				case FZEROLESSTHAN:
					zero_less_than();
					prog_cnt++;
					break;
				case FZEROLESSOREQUAL:
					zero_less_or_equal();
					prog_cnt++;
					break;
				case FZERONOTEQUALS:
					zero_not_equals();
					prog_cnt++;
					break;
				case FZEROEQUALS:
					zero_equals();
					prog_cnt++;
					break;
				case FZEROGREATERTHAN:
					zero_greater_than();
					prog_cnt++;
					break;
				case FZEROGREATEROREQUAL:
					zero_greater_or_equal();
					prog_cnt++;
					break;
				case FBYE:
					bye();
					prog_cnt++;
					break;
				case FDUP:
					dup();
					prog_cnt++;
					break;
				case FSWAP:
					swap();
					prog_cnt++;
					break;
				case FPRINT:
					//PRING
					print();
					prog_cnt++;
					break;
				case FDEF:
					function_state++;
					prog_cnt++;
					break;
				case FCALL:
					push_if_stack(prog_cnt);
					prog_cnt = prog[prog_cnt + 1];
					break;
				case FRET:
					prog_cnt = pop_if_stack();
					prog_cnt += 2;
					break;
				default:
					printf("undefined code: %d prog: %d\n",prog_cnt,prog[prog_cnt]);
					bye();
					break;
			}
		} else {
			//printf("In function state: %d\n",function_state);
			switch(prog[prog_cnt]) {
				case FDEF:
					//printf("FDEF\n");
					function_state++;
					prog_cnt++;
					break;
				case FRET:
					//printf("FRET\n");
					prog_cnt += 1;
					function_state--;
					break;
				case FCALL:
					//printf("FCALL\n");
					prog_cnt += 2;
					break;
				default:
					prog_cnt++;
					break;
			}
		}
	}
	if(mode == REPL) {
		prog_cnt = parse_idx;
	}
}
