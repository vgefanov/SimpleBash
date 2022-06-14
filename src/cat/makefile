CC = gcc

all: rebuild

s21_cat: 
	$(CC) s21_cat.c -o s21_cat

test:	rebuild
	bash test.sh

clean:
	rm -f *.out s21_cat_result.txt std_cat_result.txt s21_cat

rebuild: clean s21_cat

leaks: s21_cat
	CK_FORK=no leaks --atExit -- ./s21_cat

linter: 
	python3 ../../materials/linters/cpplint.py --extensions=c *.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c
