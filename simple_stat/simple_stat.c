#include <stddef.h>
#include <stdlib.h>

#include "simple_stat.h"

/* max array size */
#define MAX_ARRAY_SIZE 1048575

#define UINT32_MAX 4294967295
#define INT32_MAX 2147483647
#define INT32_MIN -2147483648

static inline int
abs_(int x) {
    return x > 0 ? x : -x;
}

/* will calculate average from array of
 * int as absolute values.
 * Is working with values in between (0, 4294967295).
 *
 * Params:
 *      int *values: array of values;
 *      int size: size of array (will use control value).
 * Returns:
 *      double: abs average. */
double
abs_average(int values[], int size) {
    unsigned int sum = 0, i = 0, abs_value = 0;

    for (i = 0; (i < size && i < MAX_ARRAY_SIZE); i++) {
        abs_value = (unsigned int) abs_(values[i]);
        if ((UINT32_MAX - sum) < abs_value) {
            abort();
        }

        sum += abs_value;
    }

    if (i == 0)
        abort();
    return ((double)sum / (double)i); 
}

/* will calculate average from array of
 * int. For calculation average with negative
 * values.
 * Is working with values (-2147483648, 2147483647)
 *
 * Params:
 *      int *values: array of values;
 *      int size: size of array (will use control value).
 * Returns:
 *      double: average. */
double
average(int values[], int size) {
    int sum = 0, i = 0, value = 0;

    for (i = 0; (i < size && i < MAX_ARRAY_SIZE); i++) {
        value = values[i];
        if ((sum < 0) && (value < 0)) {

            if ((sum + value) > 0)
                abort();

        }

        if ((sum > 0) && (value > 0)) {
            if ((sum + value) < 0)
                abort();
        }

        sum += value;
    }

    if (i == 0)
        abort();
    return (double)sum / (double)i; 
}

double
median(int values[], int size, int (*fnc)(const void*, const void*)) {
    int mid = 0, _a_size = 0;

    if (size <= 0) 
        abort();

    qsort(values, size, sizeof(values[0]), fnc);

    mid = size / 2;
    if (size % 2) {

        int _mid[2] = {values[mid], values[mid + 1]};
        _a_size = sizeof(_mid) / sizeof(_mid[0]);

        return average(_mid, _a_size);
    }

    return (double) values[mid];
}

int *mode(int values[]) {
    int *modes = NULL;
    return modes;
}

int median_amplitude(int values[]) {
    return 0;
}

