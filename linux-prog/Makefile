build: hi_c libHiCpp

hi_c: hello.c
	gcc -Wall -g -D MLIBCPP -fPIC -ldl hello.c -o hi_c

libHiCpp: hi_lib.c hi_lib.h
	gcc -Wall -g -o libHiCpp.so -shared -fPIC hi_lib.c

clean:
	-rm *.o libHiCpp.so 2>mkferr.txt
