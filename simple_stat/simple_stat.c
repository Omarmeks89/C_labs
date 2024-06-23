#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "measurements.h"
#include "err_codes.h"
#include "simple_stat.h"

static int
abs_(int v, int *res) {
    if (res == NULL) 
        return NULADR;

    if (v == INT32_MIN)
        return GOTOVF;

    *res = v > 0 ? v : -v;
    return 0;
}

/* will calculate average from array of
 * int as absolute values.
 * Is working with values in between (0, 2147483647).
 *
 * Params:
 *      int *values: array of values;
 *      int size: size of array (will use control value).
 * Returns:
 *      double: abs average. */
int
abs_average(measurements m, double *abs_avg) {
    int sum = 0, i = 0, abs_value = 0, st = 0, tmp = -1;

    if ((m == NULL) || (abs_avg == NULL))
        return NULADR;

    for (i = 0; i < len(m); i++) {
        tmp = get_value(m, i);
        st = abs_(tmp, &abs_value);

        if (st != SUCCESS)
            return st;

        if ((INT32_MAX - sum) < abs_value)
            return GOTOVF;

        sum += abs_value;
    }

    if (i == 0)
        return NOITER;

    *abs_avg = ((double)sum / (double)i); 
    return SUCCESS;
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
int
average(measurements m, double *avg) {
    int sum = 0, i = 0, value = 0;

    if ((m == NULL) || (avg == NULL))
        return NULADR;

    for (i = 0; i < len(m); i++) {
        value = get_value(m, i);

        if ((sum < 0) && (value < 0)) {

            if ((sum + value) > 0)
                return GOTOVF;

        }

        if ((sum > 0) && (value > 0)) {
            if ((sum + value) < 0)
                return GOTOVF;
        }

        sum += value;
    }

    if (i == 0)
        return NOITER;

    *avg = (double)sum / (double)i; 
    return SUCCESS;
}

static int
abs_arraycp(int dest[], const int src[], int size) {
    int i = 0, tmp = 0, st = 0;

    if ((src == NULL) || (dest == NULL))
        return NULADR;

    if ((size <= 0) || (size > MAX_ARRAY_CAPASITY))
        return INVDIM;

    for (i = 0; i < size; i++) {
        st = abs_(src[i], &tmp);

        if (st != 0)
            return st;

        dest[i] = tmp;
    }

    return i;
}

int
median(measurements m, double *median_v, int (*fnc)(const void*, const void*)) {
    int mid = 0, copied = 0;
    int *arr_copy;

    if ((m == NULL) || (median_v == NULL) || (fnc == NULL))
        return NULADR;

    if (len(m) == 0)
        return NODATA;

    arr_copy = (int *) malloc(len(m) * sizeof(int));
    if (arr_copy == NULL)
        return NULADR;

    copied = copy_measurements_array(m, arr_copy);
    if (copied != len(m)) {
        free(arr_copy);
        return NEQUAL;
    }

    /* TODO: separate */
    qsort(arr_copy, len(m), sizeof(int), fnc);

    mid = len(m) / 2;

    if ((len(m) > 1) && (len(m) % 2 == 0)) {
        *median_v = _AVG_AB(arr_copy[mid - 1], arr_copy[mid]);
    } else {
        *median_v = (double) arr_copy[mid];
    }

    free(arr_copy);
    return SUCCESS;
}

static inline int
_abs_compare(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);
}

int
abs_median(measurements m, double * median_v) {
    int mid = 0, i = 0, tmp = 0, abs_value = 0, st = -1;
    int *arr_copy;

    if ((m == NULL) || (median_v == NULL))
        return NULADR;

    if (len(m) == 0)
        return NODATA;

    arr_copy = (int *) malloc(len(m) * sizeof(int));
    if (arr_copy == NULL)
        return NULADR;

    for (i = 0; i < len(m); i++) {
        tmp = get_value(m, i);
        st = abs_(tmp, &abs_value);

        if (st != SUCCESS) {
            free(arr_copy);
            return st;
        }

        arr_copy[i] = abs_value;
    }

    /* TODO: separate */
    qsort(arr_copy, len(m), sizeof(int), &_abs_compare);

    mid = len(m) / 2;

    if ((len(m) > 1) && (len(m) % 2 == 0)) {
        *median_v = _AVG_AB(arr_copy[mid - 1], arr_copy[mid]);
    } else {
        *median_v = (double) arr_copy[mid];
    }

    free(arr_copy);
    return SUCCESS;
}

int
dispersion(measurements m, double *dispn) {
    double abs_avg = 0.0, total = 0.0, tmp = 0.0;
    int res = 0, i = 0;

    if ((m == NULL) || (dispn == NULL))
        return NULADR;

    res = abs_average(m, &abs_avg);
    if (res != SUCCESS)
        return res;

    for (i = 0; i < len(m); i++) {
        tmp = fabs((double) m->arr[i] - abs_avg);
        tmp = pow(tmp, 2);
        if (fabs(DBL_MAX - total) < tmp)
            return GOTOVF;

        total += tmp;
    }
    if (i == 0)
        return NOITER;

    *dispn = total / (double) len(m);
    return SUCCESS;
}
