printf "test 1 without any flag\n" >> std_cat_result.txt
printf "test 1 without any flag\n" >> s21_cat_result.txt
cat test1.txt >> std_cat_result.txt
./s21_cat test1.txt >> s21_cat_result.txt

printf "test 2 without any flag\n" >> std_cat_result.txt
printf "test 2 without any flag\n" >> s21_cat_result.txt
cat test2.txt >> std_cat_result.txt
./s21_cat test2.txt >> s21_cat_result.txt

printf "test 3 -b flag\n" >> std_cat_result.txt
printf "test 3 -b flag\n" >> s21_cat_result.txt
cat -b test1.txt >> std_cat_result.txt
./s21_cat -b test1.txt >> s21_cat_result.txt

printf "test 4 -b flag\n" >> std_cat_result.txt
printf "test 4 -b flag\n" >> s21_cat_result.txt
cat -b test2.txt >> std_cat_result.txt
./s21_cat -b test2.txt >> s21_cat_result.txt

printf "test 5 -e flag\n" >> std_cat_result.txt
printf "test 5 -e flag\n" >> s21_cat_result.txt
cat -e test1.txt test2.txt >> std_cat_result.txt
./s21_cat -e test1.txt test2.txt >> s21_cat_result.txt

printf "test 6 -n flag\n" >> std_cat_result.txt
printf "test 6 -n flag\n" >> s21_cat_result.txt
cat -n test1.txt >> std_cat_result.txt
./s21_cat -n test1.txt >> s21_cat_result.txt

printf "test 7 -s flag\n" >> std_cat_result.txt
printf "test 7 -s flag\n" >> s21_cat_result.txt
cat -s test1.txt test2.txt >> std_cat_result.txt
./s21_cat -s test1.txt test2.txt >> s21_cat_result.txt

printf "test 8 -t flag\n" >> std_cat_result.txt
printf "test 8 -t flag\n" >> s21_cat_result.txt
cat -t test1.txt >> std_cat_result.txt
./s21_cat -t test1.txt >> s21_cat_result.txt

printf "test 9 -v flag\n" >> std_cat_result.txt
printf "test 9 -v flag\n" >> s21_cat_result.txt
cat -v test1.txt >> std_cat_result.txt
./s21_cat -v test1.txt >> s21_cat_result.txt

printf "test 10 -s -e flag\n" >> std_cat_result.txt
printf "test 10 -s -e flag\n" >> s21_cat_result.txt
cat -s -e test1.txt test2.txt >> std_cat_result.txt
./s21_cat -s -e test1.txt test2.txt >> s21_cat_result.txt

diff std_cat_result.txt s21_cat_result.txt
