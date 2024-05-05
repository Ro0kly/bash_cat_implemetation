all:
	gcc -Wall -Werror -Wextra cat.c
	./a.out cat -b a.txt