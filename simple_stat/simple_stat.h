#ifndef _SIMPLE_STAT_H
#define _SIMPLE_STAT_H

#ifdef __cplusplus
extern "C"
#endif

/* max array size */
#define MAX_ARRAY_SIZE 1048575

#define UINT32_MAX 4294967295
#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

double
abs_average(int values[], int size);

#endif /* _SIMPLE_STAT_H */
