#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read.h"
#include "prog.h"
#include "control.h"
#include "word.h"
#include "eval.h"

const char *sep = " \t\n\xd\xa";
char proc_diable_cnt = 0;
int parse_idx = 0;


//ファイルからプログラムを読みこんだバッファを返す
char* load_prog(char *fname)
{
	FILE *fp;
	unsigned int idx = 0;
	char c;
	//Array counter
	int buf_size = 100;
	char* cmd;
	cmd = (char *)malloc(sizeof(char) * buf_size);
	if(cmd == NULL) {
		fprintf(stderr,"Malloc Error!!\n");
		exit(1);
	}
	fp = fopen(fname, "r");
	while ((c = fgetc(fp)) != EOF) {
		cmd[idx++] = c;
		if(idx == (buf_size - 10)) {
			cmd = (char *)realloc(cmd,sizeof(char) * (buf_size + 10));
			if(cmd == NULL) {
				fprintf(stderr,"Realloc Error!!\n");
				exit(1);
			}
			else {
				buf_size += 10;
			}
		}
	}
	cmd[idx] = '\x0';
	fclose(fp);
	return cmd;
}


//プログラムが読みこまれたバッファを引数にとり、プログラムスタックに登録する
void parse(char **cmd)
{
	char *token;
	char adrs;
	int j;
	token = strtok(*cmd, sep);
	if(prog_stack_size == 0) {
		prog = (char *)malloc(sizeof(char) * 100);
		if(prog == NULL) {
			fprintf(stderr, "Malloc Error!!\n");
			exit(1);
		}
		prog_stack_size = 100;
	}
	for (j = 0; j < sizeof(prog) / sizeof(char); j++) {
		prog[j] = FEND;
	}
	while(token != NULL) {
		printf("Parse idx: %d\n",parse_idx);
		if((prog_stack_size - 10) <= parse_idx && parse_idx <= prog_stack_size) {
			prog = (char *)realloc(prog,sizeof(char) * (prog_stack_size + 10));
			if(prog == NULL) {
				fprintf(stderr, "Realloc Error!!\n");
				exit(1);
			}
			else {
				//We must initialize stack
				for (j = prog_stack_size; j < (prog_stack_size + 10); j++) {
					prog[j] = FEND;
				}
				printf("program size update from: %d",prog_stack_size);
				prog_stack_size += 10;
				printf(" to: %d",prog_stack_size);
			}
		}
		if(strcmp(token, "+") == 0) {
			prog[parse_idx] = FPLUS;
			parse_idx++;
		}
		else if(strcmp(token, "-") == 0) {
			prog[parse_idx] = FMINUS;
			parse_idx++;
		}
		else if(strcmp(token, "/") == 0) {
			prog[parse_idx] = FREM;
			parse_idx++;
		}
		else if(strcmp(token, "*") == 0) {
			prog[parse_idx] = FTIMES;
			parse_idx++;
		}
		else if(strcmp(token, "mod") == 0) {
			prog[parse_idx] = FMOD;
			parse_idx++;
		}
		else if(strcmp(token, "<") == 0) {
			prog[parse_idx] = FLESSTHAN;
			parse_idx++;
		}
		else if(strcmp(token, "<=") == 0) {
			prog[parse_idx] = FLESSOREQUAL;
			parse_idx++;
		}
		else if(strcmp(token, "<>") == 0) {
			prog[parse_idx] = FNOTEQUALS;
			parse_idx++;
		}
		else if(strcmp(token, "=") == 0) {
			prog[parse_idx] = FEQUALS;
			parse_idx++;
		}
		else if(strcmp(token, ">") == 0) {
			prog[parse_idx] = FGREATERTHAN;
			parse_idx++;
		}
		else if(strcmp(token, ">=") == 0) {
			prog[parse_idx] = FGREATEROREQUAL;
			parse_idx++;
		}
		else if(strcmp(token, "0<") == 0) {
			prog[parse_idx] = FZEROLESSTHAN;
			parse_idx++;
		}
		else if(strcmp(token, "0<=") == 0) {
			prog[parse_idx] = FZEROLESSOREQUAL;
			parse_idx++;
		}
		else if(strcmp(token, "0<>") == 0) {
			prog[parse_idx] = FZERONOTEQUALS;
			parse_idx++;
		}
		else if(strcmp(token, "0=") == 0) {
			prog[parse_idx] = FZEROEQUALS;
			parse_idx++;
		}
		else if(strcmp(token, "0>") == 0) {
			prog[parse_idx] = FZEROGREATERTHAN;
			parse_idx++;
		}
		else if(strcmp(token, "0>=") == 0) {
			prog[parse_idx] = FZEROGREATEROREQUAL;
			parse_idx++;
		}
		else if(strcmp(token, "drop") == 0) {
			prog[parse_idx] = FPOP;
			parse_idx++;
		}
		else if(strcmp(token, "swap") == 0) {
			prog[parse_idx] = FSWAP;
			parse_idx++;
		}
		else if(strcmp(token, "dup") == 0) {
			prog[parse_idx] = FDUP;
			parse_idx++;
		}
		else if(strcmp(token, "if") == 0) {
			prog[parse_idx] = FIF;
			push_if_stack(parse_idx+1);
			parse_idx += 2;
			proc_disable_cnt++;
		}
		else if(strcmp(token, "else") == 0) {
			prog[parse_idx] = FELSE;
			prog[pop_if_stack()] = parse_idx + 2;
			push_if_stack(parse_idx + 1);
			parse_idx += 2;
		}
		else if(strcmp(token, "then") == 0) {
			prog[parse_idx] = FTHEN;
			prog[pop_if_stack()] = parse_idx + 1;
			parse_idx++;
			proc_disable_cnt--;
		}
		else if(strcmp(token, ":") == 0) {
			prog[parse_idx] = FDEF;
			parse_idx++;
			token = strtok(NULL,sep);
			assoc_word_name(token);
			proc_disable_cnt++;
		}
		else if(strcmp(token, ";") == 0) {
			prog[parse_idx] = FRET;
			parse_idx++;
			prog_cnt = parse_idx;
			//printf("Current prog_cnt: %d\n",prog_cnt);
			proc_disable_cnt--;
		}
		else if(strcmp(token, ".") == 0) {
			prog[parse_idx] = FPRINT;
			parse_idx++;
		}
		else if(strcmp(token, "bye") == 0) {
			prog[parse_idx] = FBYE;
			parse_idx++;
		}
		else if((adrs = get_word_address(token)) >= 0) {
			//printf("ADRS: %d\n",adrs);
			prog[parse_idx] = FCALL;
			prog[parse_idx + 1] = word_proc[(int)adrs].proc_pointer;
			parse_idx += 2;
		}
		else if(isnum(token)) {
			prog[parse_idx] = FPUSH;
			prog[parse_idx + 1] = atoi(token);
			parse_idx += 2;
		}
		else {
			printf("undefined word: %s\n", token);
			exit(1);
		}
		token = strtok(NULL,sep);
	}
	prog[parse_idx] = FEND;
	if(mode == REPL) {
		base_prog_cnt = parse_idx;
	}
}

void get_token(char **cmd, char *token)
{
	int c;
	int j = 0;
	token[0] = '\x0';
	c = **cmd;
	*cmd = *cmd + 1;
	while(c != ' ' && **cmd != '\x0') {
		c = **cmd;
		*cmd = *cmd + 1;
	}
	while(c != ' ' && **cmd != '\x0') {
		token[j] = c;
		j++;
		c = **cmd;
		*cmd = *cmd + 1;
	}
	token[j] = '\x0';
}

int isnum(char *str) {
	if(*str == '+' || *str == '-') {
		*str++;
	}
	while(*str != '\x0') {
		if(!isdigit(*str)) {
			return 0;
		}
		str++;
	}

	return 1;
}

//ファイルをバッファに入れて、プログラムスタックにいれるまでを一回でやる関数
void load_file(char *fname)
{
	char *cmd;
	cmd = load_prog(fname);
	parse(&cmd);
	eval_prog();
}
