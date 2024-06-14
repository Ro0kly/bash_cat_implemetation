s_cat:
	gcc -Wall -Werror -Wextra cat.c -o s_cat

clean:
	rm -rf s_cat

rebuild:
	make clean
	make s_cat