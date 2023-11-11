CC=gcc
CFLAGS=-Wall -Wextra -Wuninitialized -MMD -g -fdiagnostics-color=auto
LDFLAGS=
SRC=main.c pile.c
OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))

prog: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

debug.c: pile.c
	gcc -E $@ $^ > debug.c

clean:
	rm -rf build
	rm -rf debug.c

-include $(DEP)
