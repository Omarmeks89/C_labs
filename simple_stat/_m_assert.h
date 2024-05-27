#ifndef _M_ASSERT_H
#define _M_ASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LINE() (__LINE__)

#define __eq_int32(a, b) ((int) a == (int) b)

#define __ne_int32(a, b) ((int) a != (int) b)

#define __eq_double64(a, b, eps) ((fabs((double) a - (double) b) <= (double) eps))

#define __ne_double64(a, b, eps) ((fabs((double) a - (double) b) > (double) eps))

/* ASSERT_EQ check that two args are equal
 * or will abort execution. */
#define ASSERT_EQ_INT32(RES, EXP, LINE) \
    { \
        int success = 0; \
        success = __eq_int32(RES, EXP); \
        if (success) { \
            printf("(LINE: %6s) PASSED. [EXPECTED: %d, GOT: %d]\n", LINE, EXP, RES); \
        } else { \
            printf("(LINE: %6s) FAILED. [EXPECTED: %d, GOT: %d]\n", LINE, EXP, RES); \
            abort(); \
        } \
    }

/* will not abort() routine execution, only
 * write to stderr about test failure or success. */
#define EXPECT_EQ_INT32(RES, EXP, LINE) \
    { \
        int success = 0; \
        success = __eq_int32(RES, EXP); \
        if (success) { \
            printf("(LINE: %6s) PASSED. [EXPECTED: %d, GOT: %d]\n", LINE, EXP, RES); \
        } else { \
            printf("(LINE: %6s) FAILED. [EXPECTED: %d, GOT: %d]\n", LINE, EXP, RES); \
        } \
    }

/* assert to double */
#define ASSERT_EQ_DBL(RES, EXP, EPSILON, LINE) \
    { \
        int success = 0; \
        success = __eq_double64(RES, EXP, EPSILON); \
        if (success) { \
            printf("(LINE: %6s) PASSED. [EXPECTED: %.6lf, GOT: %.6lf]\n", LINE, EXP, RES); \
        } else { \
            printf("(LINE: %6s) FAILED. [EXPECTED: %.6lf, GOT: %.6lf]\n", LINE, EXP, RES); \
            abort(); \
        } \
    }

#endif /* _M_ASSERT_H */
