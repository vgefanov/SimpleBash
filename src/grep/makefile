CC = gcc

all: rebuild

s21_grep: 
	$(CC) s21_grep.c -o s21_grep

test:	rebuild
	bash test.sh

clean:
	rm -f *.out s21_grep_result.txt std_grep_result.txt s21_grep

rebuild: clean s21_grep

leaks: s21_grep
	CK_FORK=no leaks --atExit -- ./s21_grep

linter: 
	python3 ../../materials/linters/cpplint.py --extensions=c *.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c
