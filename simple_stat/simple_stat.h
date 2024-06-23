#pragma once

#ifndef _SIMPLE_STAT_H
#define _SIMPLE_STAT_H

#ifdef __cplusplus
extern "C"
#endif

#include <stddef.h>

#include "measurements.h"

#define UINT32_MAX 4294967295
#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

#define _AVG_AB(a, b) (((double) (a + b)) / 2.0)

int abs_average(measurements m, double * abs_avg);
int average(measurements m, double * avg);
int median(measurements m, double * median_v,
           int (* fnc)(const void *, const void *));
int abs_median(measurements m, double * median_v);
int dispersion(measurements m, double * dispn);

#endif /* _SIMPLE_STAT_H */
