s21_cat:
	gcc -Wall -Werror -Wextra cat.c -o s21_cat

clean:
	rm -rf s21_cat

rebuild:
	make clean
	make s21_cat