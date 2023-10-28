#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
/* lib below for dynamic linking */
#include <dlfcn.h>
#include <stdlib.h>

#define _argc_cnt 4
#define _libname 1
#define _funcname 2
#define _number 3

/* lib function prototype */
int (*someSecretFunctionPrototype)(int);

void *initlib(const char *libname) {
    void *handler = dlopen(libname, RTLD_LAZY | RTLD_LOCAL);
    if (handler == NULL)
        return NULL;
    return handler;
}

int call_func(void *handle, const char *symname, int arg) {
    someSecretFunctionPrototype = (int (*)(int))dlsym(handle, symname);
    if (someSecretFunctionPrototype == NULL)
        return 1;
    return someSecretFunctionPrototype(arg);
}

/* close shared object and dump it from mem
 * Closing at the moment not guaranteed */
bool dumplib(void *handle) {
    int closed = dlclose(handle);
    if (closed != 0)
        return false;
    return true;
}

int main(int argc, char *argv[]) {
    int res = 0, ex_stat = 1;
    if (argc != _argc_cnt) {
        printf("Not enough args. Got %d, need %d\n", argc, _argc_cnt);
        goto done;
    }
    void *hnd = initlib(argv[_libname]);
    if (hnd != NULL) {
        res = call_func(hnd, argv[_funcname], atoi(argv[_number]));
        if (res == 1)
            goto done;
        printf("%d\n", res);
        ex_stat = 0;
    }
done:
    return ex_stat;
}
