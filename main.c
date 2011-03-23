#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "stack.h"
#include "calc.h"
#include "prog.h"
#include "read.h"
#include "readLine.h"
#include "eval.h"
#include "control.h"

enum ePROG eprog;
int quit_enabled = 0;
int mode = LOAD;

void greeting(void);

int main(int argc, char** argv) {
	char *cmd_buf;
	int j;
	for (j = 0; j < sizeof(prog) / sizeof(char); j++) {
		prog[j] = FEND;
	}
	//load_stdlib();
	if(argc >= 2) {
		mode = LOAD;
		load_file(argv[1]);
	}
	else {
		mode = REPL;
		greeting();
		while(!quit_enabled) {
			printf(">>");
			cmd_buf = readLine();
			parse(&cmd_buf);
			if(!proc_disable_cnt) {
				eval_prog();
			}
		}
	}
  return 0;
}

void greeting(void)
{
	printf("\tMY FORTH DEVELOP BY POCKET\n");
}

void load_stdlib()
{
	load_file("stdlib.f");
}
