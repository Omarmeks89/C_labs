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

/* grow called when we need alloc or realloc memory
 * for measurements array. If aray size < 2048, it
 * will grow as 2x, if array size > 2048, it will grow
 * as x + 512.
 *
 * Params:
 *  m:              pointer on measurements struct;
 *
 * Return:
 *  - GOTOVF:       if current grow will be bigger as MAX_ARRAY_CAPASITY;
 *  - NULADR:       if m == NULL (empty pointer);
 *  - NALLOC:       if nested array was not allocated. */
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
            return GOTOVF;
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
 *  - size:     wiched measurements array size;
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

/* free_measurements free allocated memory
 * for measurements struct.
 *
 * Params:
 *  - m:            pointer on measurements struct;
 *
 * Return:
 *  - NULADR:       if m == NULL;
 *  - SUCCESS:      if memory was deallocated.  */
int
free_measurements(measurements m) {
    if (m == NULL)
        return NULADR;

    if (m->arr != NULL)
        free(m->arr);

    free(m);
    return SUCCESS;
}

/* len return len of 
 * nested array. Len is equal to elements count.
 *
 * Params:
 *  - m:            pointer on mesurements struct;
 *
 * Return:
 *  -               len of array (size_t type). */
size_t
len(measurements m) {
    return m->len;
}

/* append new element into array.
 * When capasity is full, array will be grow if
 * capasity is less than MAX_ARRAY_CAPASITY.
 *
 * Params:
 *  - m:            pointer on measurement struct;
 *  - value:        value to append;
 *
 * Return:
 *  - NULADR:       if m == NULL (empty pointer);
 *  - GOTOVF:       if next grow will be bigger as MAX_ARRAY_CAPASITY;
 *  - NALLOC:       if memory for new array is not alocated. */
int
append(measurements m, int value) {
    int code = 0;

    if (m == NULL)
        return NULADR;

    if (m->len == m->cap) {
        code = grow(m);

        if (code != SUCCESS) {
            return code;
        }
    } 

    m->arr[m->pos] = value;
    m->len++;
    m->cap++;

    return SUCCESS;
}

/* get_value return value by wished position.
 * If osition is invalid will return error.
 *
 * Params:
 *  - m:            pointer on measurements struct;
 *  - pos:          wished position of stored value.
 *                  If position is bigger that position
 *                  inside a measurements struct, or 
 *                  m == NULL (is an empty pointer), subroutine
 *                  will be aborted.
 *
 * Return:
 *  -               value by current position. */
int
get_value(measurements m, int pos) {
    if ((m == NULL) || (m->pos < pos)) {
        perror("get_value: nulptr or invalid pos.");
        abort();
    }

    return m->arr[pos];
}

/* copy_measurements_array copy all elements
 * into dest[] array. If m or dest are invalid pointers
 * will return NULADR.
 *
 * Params:
 *  - m :           pointer on measurements struct;
 *  - dest[]:       pointer on valid destination array;
 *
 * Return:
 *  -               size of copyed bytes (size_t). */
size_t 
copy_measurements_array(measurements m, int dest[]) {
    size_t i = 0;

    if ((m == NULL) || (dest == NULL))
        return -1;

    for (i = 0; i < m->len; i++) {
        dest[i] = m->arr[i];
    }

    return i;
}
