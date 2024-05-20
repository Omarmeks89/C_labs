LIB_NAME=primes

# extra gcc flags
EXTRA=-Wall -Wextra -Werror
C_STD=-std=c99

build:
	gcc -g $(EXTRA) $(C_STD) -DDEBUG main.c -o $(LIB_NAME)

clean:
	rm -f *.o

valgrind_check:
	valgrind -s --track-origins=yes --leak-check=full ./$(LIB_NAME)
