printf "test 1 without any flag\n" >> std_grep_result.txt
printf "test 1 without any flag\n" >> s21_grep_result.txt
grep as test1.txt >> std_grep_result.txt
./s21_grep as test1.txt >> s21_grep_result.txt

printf "test 2 without any flag\n" >> std_grep_result.txt
printf "test 2 without any flag\n" >> s21_grep_result.txt
grep zx test2.txt >> std_grep_result.txt
./s21_grep zx test2.txt >> s21_grep_result.txt

printf "test 3 -e flag\n" >> std_grep_result.txt
printf "test 3 -e flag\n" >> s21_grep_result.txt
grep -e a test1.txt >> std_grep_result.txt
./s21_grep -e a test1.txt >> s21_grep_result.txt

printf "test 4 -i flag\n" >> std_grep_result.txt
printf "test 4 -i flag\n" >> s21_grep_result.txt
grep -i d test.txt test1.txt >> std_grep_result.txt
./s21_grep -i d test.txt test1.txt >> s21_grep_result.txt

printf "test 5 -v flag\n" >> std_grep_result.txt
printf "test 5 -v flag\n" >> s21_grep_result.txt
grep -v dsa test.txt test1.txt >> std_grep_result.txt
./s21_grep -v dsa test.txt test1.txt >> s21_grep_result.txt

printf "test 6 -c flag\n" >> std_grep_result.txt
printf "test 6 -c flag\n" >> s21_grep_result.txt
grep -c s test.txt test1.txt >> std_grep_result.txt
./s21_grep -c s test.txt test1.txt >> s21_grep_result.txt

printf "test 7 -l flag\n" >> std_grep_result.txt
printf "test 7 -l flag\n" >> s21_grep_result.txt
grep -l  ad test.txt test1.txt >> std_grep_result.txt
./s21_grep -l ad test.txt test1.txt >> s21_grep_result.txt

printf "test 8 -n flag\n" >> std_grep_result.txt
printf "test 8 -n flag\n" >> s21_grep_result.txt
grep -n sd test.txt test1.txt >> std_grep_result.txt
./s21_grep -n sd test.txt test1.txt >> s21_grep_result.txt

printf "test 9 -h flag\n" >> std_grep_result.txt
printf "test 9 -h flag\n" >> s21_grep_result.txt
grep -h qw test.txt test1.txt >> std_grep_result.txt
./s21_grep -h qw test.txt test1.txt >> s21_grep_result.txt

printf "test 10 -s flag\n" >> std_grep_result.txt
printf "test 10 -s flag\n" >> s21_grep_result.txt
grep -s 12 test.txt test1.txt test4.txt >> std_grep_result.txt
./s21_grep -s 12 test.txt test1.txt test4.txt >> s21_grep_result.txt

# printf "test 11 -f flag\n" >> std_grep_result.txt
# printf "test 11 -f flag\n" >> s21_grep_result.txt
# grep -f zx test.txt test1.txt >> std_grep_result.txt
# ./s21_grep -f zx test.txt test1.txt >> s21_grep_result.txt

printf "test 12 -o flag\n" >> std_grep_result.txt
printf "test 12 -o flag\n" >> s21_grep_result.txt
grep -o qwerty test.txt test1.txt >> std_grep_result.txt
./s21_grep -o qwerty test.txt test1.txt >> s21_grep_result.txt

printf "test 13 -iv flag\n" >> std_grep_result.txt
printf "test 13 -iv flag\n" >> s21_grep_result.txt
grep -iv asdf test.txt test1.txt >> std_grep_result.txt
./s21_grep -iv asdf test.txt test1.txt >> s21_grep_result.txt

printf "test 14 -in flag\n" >> std_grep_result.txt
printf "test 14 -in flag\n" >> s21_grep_result.txt
grep -in qaz test.txt test1.txt >> std_grep_result.txt
./s21_grep -in qaz test.txt test1.txt >> s21_grep_result.txt

diff std_grep_result.txt s21_grep_result.txt

rm std_grep_result.txt s21_grep_result.txt
