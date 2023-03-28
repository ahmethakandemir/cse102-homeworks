all: compile run clean

compile: main.c util.c util.h

	@gcc -o test main.c util.c

run:

	@./test


clean:

	@rm -f *.o
	@rm -f test
