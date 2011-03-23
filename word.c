#include <stdio.h>
#include <string.h>
#include "word.h"
#include "prog.h"
#include "read.h"
char reg_word_name(char *str)
{
	char reg_pos = word_heap_index;
	while(*str != '\x0') {
		word_heap[(int)word_heap_index++] = *str++;
	}
	word_heap[(int)word_heap_index++] = '\x0';
	return reg_pos;
}

void assoc_word_name(char *name)
{
	char adrs;
	printf("Register word name: %s prog_cnt: %d\n",name, prog_cnt);
	if((adrs = get_word_address(name)) >= 0) {
		//If Already same word is registerd.
		printf("redefined %s\n",name);
		word_proc[(int)adrs].proc_pointer = parse_idx;
	}
	else {
		word_proc[(int)word_proc_head].word_pointer = reg_word_name(name);
		word_proc[(int)word_proc_head].proc_pointer = parse_idx;
		word_proc_head++;
	}
}

char get_word_address(char *name)
{
	char j;
	for(j = 0; j < 100; j++) {
		char heap_index = word_proc[(int)j].word_pointer;
		if(strcmp(&word_heap[(int)heap_index], name) == 0) {
			return j;
		}
	}

	return -1;
}
