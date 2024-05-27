#ifndef _SIMPLE_STAT_H
#define _SIMPLE_STAT_H

#ifdef __cplusplus
extern "C"
#endif

enum status {
    SUCCESS = 0,
    NOITER,
    NOTABS,
    GOTOVF,
    NULADR,
    INVDIM,
    NALLOC,
    NEQUAL,
} s_status;

#define MAX_ARRAY_SIZE 1048575

#define UINT32_MAX 4294967295
#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

int abs_average(int values[], int size, double * abs_avg);
int average(int values[], int size, double * avg);
int median(const int values[], int size,
           double * median_v, int (* fnc)(const void *, const void *));
int abs_median(const int values[], int size, double * median_v);
int dispersion(int values[], int size, double * dispn);

#endif /* _SIMPLE_STAT_H */
