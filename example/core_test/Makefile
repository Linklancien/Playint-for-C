CC ?= gcc
CFLAGS ?= -Wall -Wextra -Wpedantic -Werror
MYSTD ?= -std=c89
PROG ?= playint_core_test.out
MYOBJS ?= playint_core_test.c ../../core/playint_core.c

all : $(PROG)

$(PROG): $(MYOBJS)
	$(CC) $(MYOBJS) $(CFLAGS) -o $(PROG)

clean:
	rm $(PROG)