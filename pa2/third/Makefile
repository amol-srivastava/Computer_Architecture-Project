file = third
all: compile

compile: third.c
	gcc -Wall -Werror -fsanitize=address -g third.c -o third.out -lm

clean:
	rm third.out