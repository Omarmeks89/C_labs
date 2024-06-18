#pragma once
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#ifdef __cplusplus
extern "C"
#endif

#include <stddef.h>

#define MAX_ARRAY_CAPASITY                  (size_t) 524287

#define NULL_SIZE                           (size_t) 0
#define MIN_GROW                            (size_t) 8
#define HALF_EXP_GROW                       (size_t) 1024
#define MAX_EXP_GROW                        (size_t) 2048
#define MONOTONIC_GROW                      (size_t) 512

typedef struct stat_measurement *measurements;

measurements new_measurements(size_t cap);
int append(measurements m, int value);
size_t inline len(measurements m);
int free_measurements(measurements m);
int grow(measurements m);

#endif /* MEASUREMENTS_H */
