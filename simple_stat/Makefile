build: _m_assert.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -lm assert_test.c -o assert_eq_test

macro: _m_assert.h
	gcc -g -E -Wall -std=c99 -lm assert_test.c -o _macro

clear:
	rm -rf *.o
