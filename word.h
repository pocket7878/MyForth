#ifndef _WORD_H_
#define _WORD_H_

char word_heap[100];
char word_heap_index;

char reg_word_name(char*);
void assoc_word_name(char*);
char get_word_address(char*);

typedef struct word_proc_table {
	char word_pointer;
	char proc_pointer;
} WORD_PROC_TABLE;

WORD_PROC_TABLE word_proc[100];
char word_proc_head;

//word program stack

#endif
