CC = gcc
CFLAGS = -Wall -Werror -fsanitize=address -g
LDFLAGS = -lm

all: first.out

first.out: first.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f first.out