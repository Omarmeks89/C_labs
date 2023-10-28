#ifndef HILIB_ENTRY
#define HILIB_ENTRY

/* make lib-func proto for
 * using and link in other
 * source-code files. */
#ifdef __cplusplus
extern "C"
#endif
void print_greet(const char *name);

#endif
