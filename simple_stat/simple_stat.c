#include <stddef.h>
#include <stdlib.h>

/* add -lm compilation flag */
#include <math.h>
#include <float.h>

#include "simple_stat.h"

static int
abs_(int x, int *res) {
    
    if (res == NULL) 
        return NULADR;
    
    if (x == INT32_MIN)
        return GOTOVF;
        
    *res = x > 0 ? x : -x;
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
abs_average(int values[], int size, double *abs_avg) {
    int sum = 0, i = 0, abs_value = 0, st = 0;

    if (abs_avg == NULL)
        return NULADR;

    if ((size <= 0) || (size > MAX_ARRAY_SIZE))
        return INVDIM;

    for (i = 0; i < size; i++) {
        st = abs_(values[i], &abs_value);
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
average(int values[], int size, double *avg) {
    int sum = 0, i = 0, value = 0;

    if (avg == NULL)
        return NULADR;

    if ((size <= 0) || (size > MAX_ARRAY_SIZE))
        return INVDIM;

    for (i = 0; i < size; i++) {
        value = values[i];
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
arraycp(int dest[], const int src[], int size) {
    int i = 0;

    if ((src == NULL) || (dest == NULL))
        return NULADR;

    if ((size <= 0) || (size > MAX_ARRAY_SIZE))
        return INVDIM;

    for (i = 0; i < size; i++) {
        dest[i] = src[i];
    }

    return i + 1;
}

static int
abs_arraycp(int dest[], const int src[], int size) {
    int i = 0, tmp = 0, st = 0;

    if ((src == NULL) || (dest == NULL))
        return NULADR;

    if ((size <= 0) || (size > MAX_ARRAY_SIZE))
        return INVDIM;

    for (i = 0; i < size; i++) {
        st = abs_(src[i], &tmp);

        if (st != 0)
            return NOTABS;

        dest[i] = tmp;
    }

    return i + 1;
}

int
median(const int values[], int size, double *median_v, int (*fnc)(const void*, const void*)) {
    int mid = 0, copied = 0, res = 0;
    int *arr_copy;

    if ((size <= 0) || (size > MAX_ARRAY_SIZE))
        return INVDIM;

    arr_copy = (int *) malloc(size * sizeof(int));
    if (arr_copy == NULL)
        return NULADR;

    copied = arraycp(arr_copy, values, size);
    if (copied != size)
        return NEQUAL;

    qsort(arr_copy, size, sizeof(int), fnc);

    mid = size / 2;
    if (size % 2) {
        int _mid[2] = {values[mid], values[mid + 1]};

        res = average(_mid, 2, median_v);
        if (res != SUCCESS)
            return res;

        free(arr_copy);
        return SUCCESS;
    }

    *median_v = (double) values[mid];
    free(arr_copy);

    return SUCCESS;
}

static inline int
_abs_compare(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);
}

int
abs_median(const int values[], int size, double * median_v) {
    int mid = 0, copied = 0, res = 0;
    int *arr_copy;

    if ((size <= 0) || (size > MAX_ARRAY_SIZE))
        return INVDIM;

    arr_copy = (int *) malloc(size * sizeof(int));
    if (arr_copy == NULL)
        return NULADR;

    copied = abs_arraycp(arr_copy, values, size);
    if (copied != size)
        return NEQUAL;

    qsort(arr_copy, size, sizeof(int), &_abs_compare);

    mid = size / 2;
    if (size % 2) {
        int _mid[2] = {values[mid], values[mid + 1]};

        res = abs_average(_mid, 2, median_v);
        if (res != SUCCESS)
            return res;

        free(arr_copy);
        return SUCCESS;
    }

    *median_v = (double) values[mid];
    free(arr_copy);

    return SUCCESS;
}

int
dispersion(int values[], int size, double *dispn) {
    double abs_avg = 0.0, total = 0.0, tmp = 0.0;
    int res = 0, i = 0;

    if ((size <= 0) || (size > MAX_ARRAY_SIZE))
        return INVDIM;

    if (dispn == NULL)
        return NULADR;

    res = abs_average(values, size, &abs_avg);
    if (res != SUCCESS)
        return res;

    for (i = 0; i < size; i++) {
        tmp = fabs((double) values[i] - abs_avg);
        tmp = pow(tmp, 2);
        if (fabs(DBL_MAX - total) < tmp)
            return GOTOVF;

        total += tmp;
    }
    if (i == 0)
        return NOITER;

    *dispn = total / (double) size;
    return SUCCESS;
}
