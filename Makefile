PROGNAME = myforth
CFILES = main.c prog.c stack.c calc.c read.c eval.c control.c word.c readLine.c
HFILES = prog.h stack.h calc.h read.h eval.h control.h word.h readLine.h

all: ${CFILES}
	gcc -Wall -g -o ${PROGNAME} ${CFILES}
clean: 
	rm ${PROGNAME}
