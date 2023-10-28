#ifdef MLIBCPP
#define __m_lib_name "libHiCpp.so"
#else
#    ifdef MLIBC
#    define __m_lib_name "libHi.so"
#    endif
#endif

#if !defined(MLIBC) && !defined(MLIBCPP)
#error lang not specified. Use -D MLIBCPP or -D MLIBC
#endif

#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>

#define FUNC "print_greet"

/* lib-func prototype. */
void (*print_greet)(const char *);

/* load shared object using name. */
bool initlib(const char *name, const char *obj) {
    void *handle = dlopen(name, RTLD_LAZY | RTLD_GLOBAL);
    if (handle == NULL)
        return false;
    print_greet = (void (*)(const char*))dlsym(handle, obj);
    if (print_greet == NULL)
        return false;
    return true;
}

/* main func that we make
 * as linkable later. */
int main() {
    int rcode = 0;
    char name[] = "Egor";
    if (initlib(__m_lib_name, FUNC)) {
        print_greet(name);
    }
    else {
        printf("ERROR: Can`t load shared %s\n", __m_lib_name);
        rcode = 1;
    }
    return rcode;
}
