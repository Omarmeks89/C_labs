#include <stddef.h>

/* max array size */
#define MAX_ARRAY_SIZE 1048575

static inline int abs_(int x) {
    return x > 0 ? x : -x;
}

/* will calculate average from array of
 * int as absolute values.
 * Params:
 *      int *values: array of values;
 *      int size: size of array (will use control value).
 * Returns:
 *      double: abs average. */
double abs_average(int *values, int size) {
    int sum = 0, i = 0;

    for (i = 0; (i < size && i < MAX_ARRAY_SIZE); i++) {
        sum += abs_(values[i]);
    }

    if (i > 0)
        return sum / i; 

    return 0.0;
}

/* will calculate average from array of
 * int. Is a little bit faster than abs_average.
 * Params:
 *      int *values: array of values;
 *      int size: size of array (will use control value).
 * Returns:
 *      double: average (not abs value). */
double average(int *values, int size) {
    int sum = 0, i = 0;

    for (i = 0; (i < size && i < MAX_ARRAY_SIZE); i++) {
        sum += values[i];
    }

    if (i > 0)
        return sum / i; 

    return 0.0;
}


double median(int *values) {
    return 0.0;
}

int *mode(int *values) {
    int *modes = NULL;
    return modes;
}

int median_amplitude(int *values) {
    return 0;
}

