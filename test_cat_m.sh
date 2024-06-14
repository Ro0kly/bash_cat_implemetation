#!/bin/bash

make rebuild

gcc -Wall -Werror -Wextra cat.c -o cat

mkdir tests

echo "Check cat -b option..."
cat -b test_data.txt > tests/b_cat_test.txt
./s_cat -b test_data.txt > tests/b_my_test.txt

if diff tests/b_my_test.txt tests/b_cat_test.txt; then
    echo "cat -b flag is done."
else
    echo "Problem with flag -b."
fi

echo "Check cat -e option..."
cat -e test_data_non_print.txt > tests/e_cat_test.txt
./s_cat -e test_data_non_print.txt > tests/e_my_test.txt

if diff tests/e_my_test.txt tests/e_cat_test.txt; then
    echo "cat -e flag is done."
else
    echo "Problem with flag -e."
fi

echo "Check cat -n option..."
cat -n test_data.txt > tests/n_cat_test.txt
./s_cat -n test_data.txt > tests/n_my_test.txt

if diff tests/n_my_test.txt tests/n_cat_test.txt; then
    echo "cat -n flag is done."
else
    echo "Problem with flag -n."
fi

echo "Check cat -s option..."
cat -s test_data.txt > tests/s_cat_test.txt
./s_cat -s test_data.txt > tests/s_my_test.txt

if diff tests/s_my_test.txt tests/s_cat_test.txt; then
    echo "cat -s flag is done."
else
    echo "Problem with flag -s."
fi

echo "Check cat -t option..."
cat -t test_data_non_print.txt > tests/t_cat_test.txt
./s_cat -t test_data_non_print.txt > tests/t_my_test.txt

if diff tests/t_my_test.txt tests/t_cat_test.txt; then
    echo "cat -t flag is done."
else
    echo "Problem with flag -t."
fi