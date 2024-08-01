CC = gcc
CFLAGS = -Wall -Werror -fsanitize=address -g
LDFLAGS = -lm

all: second.out

second.out: second.c
	$(CC) $(CFLAGS) second.c -o $@ $(LDFLAGS)

clean:
	rm -f second.out