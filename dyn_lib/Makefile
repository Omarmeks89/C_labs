C=gcc
LIB=-Wall -g -shared
OBJ=-Wall -g -fPIC
build: libsolution.so clear

libsolution.so: solution.o
	$(C) $(LIB) solution.o -o libsolution.so

solution.o: solution.c
	$(C) $(OBJ) -o solution.o -c solution.c

clear: 
	rm *.o 2>>build.txt

