#include <stdio.h>

#include "solution.h"

#define __max_singed_int (int)2147483647

/* Calculate lenght of string and
 * return length * multiplier.
 * If multiplier is bigger than 2^31-1 (signed int)
 * return -1 as error. On success increment count by one. */
int stringStat(const char *string, size_t multiplier, int *count) {
    int str_len = 0;
    for(; *string; ) {
        str_len++;
        /* if we have '\0' str we can get
         * exploit on string++ after for loop. */
        string++;
    }
    /* count means count of times we call stringStat. */
    *count += 1;
    if ((multiplier > 0) && (str_len > 0)) {
        /* in case str_len = 0 we`ll have division by zero */
        int sz_check = (int)((int)multiplier / str_len);
        if (sz_check > __max_singed_int)
            return -1;
    }
    return str_len * (int)multiplier;
}
