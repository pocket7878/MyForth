#include <stdio.h>
#include <stdlib.h>
#include "readLine.h"

char* readLine(void) {
	char *line,*line1, *line2;
	char ch;
	int currentSize = 128;
	int currentReadSize = 0;
	line1 = (char *)malloc(sizeof(char) * currentSize);
	if(line1 == NULL) {
		fprintf(stderr, "Malloc Error!!\n");
		free(line1);
		exit(1);
	}
	line = line1;
	while( (ch = getchar()) != EOF ) {
		if(ch == '\n') {
			break;
		}
		if((currentReadSize + 1) >= currentSize) {
			if(line1 != NULL) {
				line2 = (char *)realloc(line1,sizeof(char) * (currentSize + 10));
				if(line2 == NULL) {
					fprintf(stderr,"Realloc Error!!\n");
					free(line1);
					exit(1);
				}
				line1 = NULL;
				line = line2;
			} else if(line2 != NULL) {
				line1 = (char *)realloc(line2,sizeof(char) * (currentSize + 10));
				if(line1 == NULL) {
					fprintf(stderr,"Realloc Error!!\n");
					free(line2);
					exit(1);
				}
				line2 = NULL;
				line = line1;
			} else {
				fprintf(stderr,"Something happen.\n");
				exit(1);
			}
			currentSize += 10;
		}
		line[currentReadSize++] = ch;
	}
		line[currentReadSize++] = '\x0';
	return line;
}
