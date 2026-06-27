CC ?= gcc
CFLAGS ?= -Wall -Wextra -Wpedantic -Werror
MYSTD ?= -std=c89
PROG ?= playint_glfw_glue_test.out
MYOBJS ?= playint_glfw_glue_test.c ../../core/playint_core.c ../../glfw_glue/playint_core.c

all : $(PROG)

$(PROG): $(MYOBJS)
	$(CC) $(MYOBJS) $(CFLAGS) -o $(PROG)

clean:
	rm $(PROG)
