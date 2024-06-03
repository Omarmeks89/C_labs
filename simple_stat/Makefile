build: int_test double_test

int_test: _m_assert.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -lm assert_test.c -o test_int32_macro

# test macro for floating point values
double_test: _m_assert.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -lm assert_dbl_test.c -o test_dbl_macro

# link with 'math' needed here, when ld is working
avg_test: stat.o stat_avg_test.o
	gcc stat.o stat_avg_test.o -o avg_test -lm

stat_avg_test.o: _m_assert.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -o stat_avg_test.o -c test/test_average_func.c

stat.o: simple_stat.c
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -c simple_stat.c -o stat.o 

clear:
	rm -rf *.o test_int32* test_dbl* avg_test
