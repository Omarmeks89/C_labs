#ifndef LIBSOLUTION_ENTRY
#define LIBSOLUTION_ENTRY

#include <stdio.h>

/* we will build lib for C/C++
 * so we should remember about 
 * mangling in C++ */
#ifdef __cplusplus
extern "C"
#endif
int stringStat(const char *string, size_t multiplier, int *count);

#endif
