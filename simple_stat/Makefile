build: int_test double_test

avg_test: stat.o stat_avg_test.o
	gcc stat.o stat_avg_test.o -o avg_test -lm

avg_test_s: stat.o stat_s_avg_test.o
	gcc stat.o stat_s_avg_test.o -o avg_test_s -lm

median_test: stat.o test_median_func.o
	gcc stat.o test_median_func.o -o median_test -lm

test_median_func.o:
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -o test_median_func.o -c test/test_median_func.c

stat_s_avg_test.o: _m_assert.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -o stat_s_avg_test.o -c test/test_s_average_func.c

stat_avg_test.o: _m_assert.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -o stat_avg_test.o -c test/test_average_func.c

# reuse it
stat.o: simple_stat.c
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -c simple_stat.c -o stat.o 

clear:
	rm -rf *.o test_int32* test_dbl* avg_test* median*
