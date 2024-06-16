#include <stddef.h>
#include <stdlib.h>

#include <math.h>
#include <float.h>

#include "simple_stat.h"

struct stat_measurement {
    int         *arr;                       /* pointer on array of int. */
    size_t      len;
};

/* new_measurements create new measurements struct
 * and return pointer.
 *
 * Params:
 *  - size: wiched measurements array size;
 *  - error: pointer on variable which will contain an error.
 *
 * Return:
 *  - measurements: pointer on created struct or NULL, if
 *  creation failed. */
measurements
new_measurements(size_t size, int *error) {
    measurements m;

    if (error == NULL)
        return NULL;

    if (size > MAX_ARRAY_CAPASITY) {
        *error = INVDIM;
        return NULL;
    }

    m = (measurements) malloc(sizeof(measurements));
    if (m == NULL) {
        *error = NULADR;
        return NULL;
    }

    m->len = 0;
    *error = SUCCESS;
    return m;
}

int
free_measurements(measurements m) {
    if (m == NULL)
        return NULADR;

    free(m);
    return SUCCESS;
}

/* _grow called when we need alloc or realloc memory
 * for measurements array */
measurements
_grow(measurements m, int *error) {
    int *_arr = NULL;
    size_t ctrl_size = 0, grown = 0;

    if (error == NULL) {
        return m;
    }

    if (m == NULL) {
        *error = NULADR;
        return NULL;
    }

    if (m->len == (size_t) 0) {
        _arr = (int *) calloc((size_t) 8, sizeof(int));
        grown = (size_t) 8;
    }

    else if (m->len <= (size_t) 1024) {
        _arr = (int *) realloc(m->arr, m->len * 2);
        grown = m->len * 2;
    }

    else if ((m->len >= (size_t) 2048) && (m->len < MAX_ARRAY_CAPASITY)) {
        ctrl_size = (size_t) (MAX_ARRAY_CAPASITY - (2048 / 4));

        if (ctrl_size < m->len) {
            *error = GOTOVF;
            return NULL;
        }

        _arr = (int *) realloc(m->arr, m->len + (size_t) (2048 / 4));
        grown = m->len + (size_t) (2048 / 4);
    }

    if (_arr == NULL) {
        *error = NALLOC;

        if (m->len != 0) { 
            free(m->arr);
            free_measurements(m);
        }

        return NULL;
    }

    m->arr = _arr;
    m->len = grown;
    return m;
}


measurements
append(measurements m, int value, int as_abs, int *error);

size_t
len(measurements m, int *error) {
    if (error == NULL)
        return (size_t) 0;

    return m->len;
}

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

    for (i = 0; i < m->len; i++) {
        tmp = m->arr[i];
        st = abs_(tmp, &abs_value);

        if (st != SUCCESS)
            return st;

        if ((INT32_MAX - sum) < abs_value)
            return GOTOVF;

        sum += abs_value;
    }

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

    for (i = 0; i < m->len; i++) {
        value = m->arr[i];
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

    *avg = (double)sum / (double)i; 
    return SUCCESS;
}

static int
arraycp(int dest[], const int src[], int size) {
    int i = 0;

    if ((src == NULL) || (dest == NULL))
        /* NULADR */
        return -1;

    if ((size <= 0) || (size > MAX_ARRAY_CAPASITY))
        /* INVDIM */
        return -2;

    for (i = 0; i < size; i++) {
        dest[i] = src[i];
    }

    return i;
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
    int mid = 0, copied = 0, res = 0;
    measurements tmp_m;
    int *arr_copy;

    if ((m == NULL) || (median_v == NULL))
        return NULADR;

    arr_copy = (int *) malloc(m->len * sizeof(int));
    if (arr_copy == NULL)
        return NULADR;

    copied = arraycp(arr_copy, m->arr, m->len);
    if ((copied != m->len) && (copied >= 0)) {
        return NEQUAL;
    }

    /* separate into func */
    if (copied < 0) {
        switch (copied) {
            case -1:
                return NULADR;
            case -2:
                return INVDIM;
            default:
                exit(1);
        }
    }

    qsort(arr_copy, m->len, sizeof(int), fnc);

    mid = m->len / 2;
    if (!(m->len % 2)) {
        int _mid[2] = {arr_copy[mid - 1], arr_copy[mid]};

        /* FIXME: refactor */
        tmp_m = (measurements) malloc(sizeof(measurements));
        if (tmp_m == NULL)
            return NULADR;

        tmp_m->arr = _mid;
        tmp_m->len = 2;

        res = average(tmp_m, median_v);
        if (res != SUCCESS)
            return res;

        free(arr_copy);
        return SUCCESS;
    }

    *median_v = (double) arr_copy[mid];
    free(arr_copy);

    return SUCCESS;
}

static inline int
_abs_compare(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);
}

int
abs_median(measurements m, double * median_v) {
    int mid = 0, copied = 0, res = 0;
    measurements tmp_m;
    int *arr_copy;

    if ((m == NULL) || (median_v == NULL))
        return NULADR;

    arr_copy = (int *) malloc(m->len * sizeof(int));
    if (arr_copy == NULL)
        return NULADR;

    copied = abs_arraycp(arr_copy, m->arr, m->len);
    if (copied != m->len)
        return NEQUAL;

    qsort(arr_copy, m->len, sizeof(int), &_abs_compare);

    mid = m->len / 2;
    if (!(m->len % 2)) {
        int _mid[2] = {arr_copy[mid], arr_copy[mid + 1]};

        /* FIXME: refactor */
        tmp_m = (measurements) malloc(sizeof(measurements));
        if (tmp_m == NULL)
            return NULADR;

        tmp_m->arr = _mid;
        tmp_m->len = 2;

        res = abs_average(tmp_m, median_v);
        if (res != SUCCESS)
            return res;

        free(arr_copy);
        return SUCCESS;
    }

    *median_v = (double) arr_copy[mid];
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

    for (i = 0; i < m->len; i++) {
        tmp = fabs((double) m->arr[i] - abs_avg);
        tmp = pow(tmp, 2);
        if (fabs(DBL_MAX - total) < tmp)
            return GOTOVF;

        total += tmp;
    }
    if (i == 0)
        return NOITER;

    *dispn = total / (double) m->len;
    return SUCCESS;
}
