#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "measurements.h"
#include "err_codes.h"

struct stat_measurement {
    int         *arr;                       /* pointer on array of int. */
    size_t      len;                        /* array size */
    size_t      cap;
    int         pos;
};

/* _grow called when we need alloc or realloc memory
 * for measurements array.
 *
 * Params:
 *  measurements: pointer on measurements struct;
 *
 * Return:
 *  int: err_code. */
static int
grow(measurements m) {
    int *_arr = NULL;
    size_t ctrl_size = 0, grown = 0;

    if (m == NULL) {
        return NULADR;
    }

    if (m->cap == NULL_SIZE) {
        _arr = (int *) calloc(MIN_GROW, sizeof(int));
        grown = MIN_GROW;
    }

    else if (m->cap <= HALF_EXP_GROW) {
        _arr = (int *) realloc(m->arr, m->cap * 2);
        grown = m->cap * 2;
    }

    else if (m->cap >= MAX_EXP_GROW) {
        ctrl_size = MAX_ARRAY_CAPASITY - MONOTONIC_GROW;

        if (ctrl_size < m->cap) {
            return INVDIM;
        }

        _arr = (int *) realloc(m->arr, m->cap + MONOTONIC_GROW);
        grown = m->cap + MONOTONIC_GROW;
    }

    if (_arr == NULL) {
        return NALLOC;
    }

    m->arr = _arr;
    m->cap = grown;
    return SUCCESS;
}

/* new_measurements create new measurements struct
 * and return pointer.
 *
 * Params:
 *  - size: wiched measurements array size;
 *
 * Return:
 *  - measurements: pointer on created struct or NULL, if
 *  creation failed. */
measurements
new_measurements(size_t cap) {
    measurements m;

    if (cap > MAX_ARRAY_CAPASITY) {
        return NULL;
    }

    m = (measurements) malloc(sizeof(measurements));
    if (m == NULL) {
        abort();
    }

    m->arr = (int *) calloc(cap, sizeof(int));
    if (m->arr == NULL) {
        free(m);
        abort();
    }

    m->len = 0;
    m->cap = cap;
    m->pos = 0;
    return m;
}

int
free_measurements(measurements m) {
    if (m == NULL)
        return NULADR;

    if (m->arr != NULL)
        free(m->arr);

    free(m);
    return SUCCESS;
}

size_t
len(measurements m) {
    return m->len;
}

int
append(measurements m, int value) {
    int code = 0;

    if (m == NULL)
        return NULADR;

    if (m->len == m->cap) {
        code = grow(m);

        if (code != SUCCESS) {
            free_measurements(m);
            return code;
        }
    } 

    m->arr[m->pos] = value;
    m->len++;
    m->cap++;

    return SUCCESS;
}

int
get_value(measurements m, int pos) {
    if ((m == NULL) || (m->pos < pos)) {
        perror("get_value: nulptr or invalid pos.");
        abort();
    }

    return m->arr[pos];
}

int 
copy_measurements_array(measurements m, int dest[]) {
    int i = 0;

    if ((m == NULL) || (dest == NULL))
        return -1;

    for (i = 0; i < m->len; i++) {
        dest[i] = m->arr[i];
    }

    return i;
}
