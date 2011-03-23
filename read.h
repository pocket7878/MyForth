#ifndef _READ_H_
#define _READ_H_

char* load_prog(char*);
void parse(char**);
void load_file(char*);
int parse_idx;
char proc_disable_cnt;
void get_token(char**, char*);
int isnum(char*);

#endif
