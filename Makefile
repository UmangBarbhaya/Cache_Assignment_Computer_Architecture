CC=gcc
LD=gcc
CFLAGS=-ggdb -Wall -pedantic -std=gnu99 -O3
LDFLAGS=


C_OBJS=transpose.o test_transpose.o
C_PROG=transpose

default: $(C_OBJS)
		$(CC) -o $(C_PROG) $(CFLAGS) $(C_OBJS)

clean:
		-rm -rf core *.o *~ "#"*"#" Makefile.bak $(PROGS) *.dSYM
