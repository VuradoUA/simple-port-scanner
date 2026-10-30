CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -g -D_POSIX_C_SOURCE=200809L
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)

portscan: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

debug: CFLAGS += -fsanitize=address,undefined
debug: clean portscan

clean:
	rm -f portscan src/*.o

.PHONY: clean debug