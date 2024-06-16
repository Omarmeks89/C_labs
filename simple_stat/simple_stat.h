#ifndef _SIMPLE_STAT_H
#define _SIMPLE_STAT_H

#ifdef __cplusplus
extern "C"
#endif

#include <stddef.h>

typedef struct stat_measurement *measurements;

enum status {
    SUCCESS = 0,
    NOITER,
    NOTABS,
    GOTOVF,
    NULADR,
    INVDIM,
    NALLOC,
    NEQUAL,
};

#define MAX_ARRAY_CAPASITY (size_t) 524287

#define UINT32_MAX 4294967295
#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

int abs_average(measurements m, double * abs_avg);
int average(measurements m, double * avg);
int median(measurements m, double * median_v,
           int (* fnc)(const void *, const void *));
int abs_median(measurements m, double * median_v);
int dispersion(measurements m, double * dispn);

/* measuremets API */
measurements new_measurements(size_t size, int *error);
measurements append(measurements m, int value, int as_abs, int *error);
size_t len(measurements m, int *error);
int free_measurements(measurements m);

#endif /* _SIMPLE_STAT_H */
