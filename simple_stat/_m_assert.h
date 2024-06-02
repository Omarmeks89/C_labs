#ifndef _M_ASSERT_H
#define _M_ASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PASSED "PASSED"
#define FAILED "FAILED"
#define EXPECTED "EXPECTED: "
#define GOT "GOT: "
#define LINE_STR "LINE: "

/* section of spaces and
 * puctuation symbols. */
#define SINGLE_SPACE " "
#define COMMA_SPACE ", "
#define SINGLE_POINT "."

/* brackets */
#define SQR_BRACKET_OPEN "["
#define SQR_BRACKET_CLOSE "]"

#define RND_BRACKET_OPEN "("
#define RND_BRACKET_CLOSE ")"

/* special symbols and
 * formatting symbols */
#define FNAME_OFFSET "%-32s"
#define LINE_NO_FMT "%6d"
#define TEST_STATUS_OFFSET "%32s"

#ifndef INT32_FMT_TEMPL
#  define INT32_FMT_TEMPL "%8d"
#endif

#ifndef INT64_FMT_TEMPL
#  define INT64_FMT_TEMPL "%16ld"
#endif

#ifndef DBL_FMT_TEMPL
#  define DBL_FMT_TEMPL "%10.6lf"
#endif

#define _T_EOL "\n"

/* macro-template for passed test message 
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d'
 * Returns:
 *   Joined literal with format directives. */
#define _PASS_MSG(__type) (             \
        FNAME_OFFSET                    \
        SINGLE_SPACE                    \
        SQR_BRACKET_OPEN                \
        EXPECTED                        \
        __type                          \
        COMMA_SPACE                     \
        GOT                             \
        __type                          \
        SQR_BRACKET_CLOSE               \
        TEST_STATUS_OFFSET              \
        SINGLE_POINT                    \
        _T_EOL)

/* macro-template for failed test message 
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d'
 * Returns:
 *   Joined literal with format directives. */
#define _FAIL_MSG(__type) (             \
        FNAME_OFFSET                    \
        SINGLE_SPACE                    \
        RND_BRACKET_OPEN                \
        LINE_STR                        \
        LINE_NO_FMT                     \
        RND_BRACKET_CLOSE               \
        SINGLE_SPACE                    \
        SQR_BRACKET_OPEN                \
        EXPECTED                        \
        __type                          \
        COMMA_SPACE                     \
        GOT                             \
        __type                          \
        SQR_BRACKET_CLOSE               \
        TEST_STATUS_OFFSET              \
        SINGLE_POINT                    \
        _T_EOL)

/* macro for set message about test pass.
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   E:      Expected value;
 *   G:      Got value. */
#define TEST_PASSED_MSG(__type, FN, E, G) (printf(_PASS_MSG(__type), #FN, E, G, PASSED))

/* macro for set message about test fail.
 * Params:
 *   __type: format string with arg type
 *           that used in 'printf' function.
 *           Example:
 *             - '%6d';
 *   FN:     function name;
 *   LN:    line no for found failed test case;
 *   E:      Expected value;
 *   G:      Got value. */
#define TEST_FAILED_MSG(__type, FN, LN, E, G) (printf(_FAIL_MSG(__type), #FN, LN, E, G, FAILED))

/* custom epsilons */
#define DBL_e_9 1e-9
#define DBL_e_8 1e-8
#define DBL_e_7 1e-7
#define DBL_e_6 1e-6
#define DBL_e_5 1e-5
#define DBL_e_4 1e-4
#define DBL_e_3 1e-3
#define DBL_e_2 1e-2
#define DBL_e_1 1e-1

/* type casting */
#define __eq_int32(a, b) ((int) a == (int) b)

#define __ne_int32(a, b) ((int) a != (int) b)

#define __eq_double64(a, b, eps) ((fabs((double) a - (double) b) <= (double) eps))

#define __ne_double64(a, b, eps) ((fabs((double) a - (double) b) > (double) eps))

#define LINE() (__LINE__)

/* ASSERT_EQ check that two args are equal
 * or will abort execution. */
#define ASSERT_EQ_INT32(RES, EXP, F_NAME, LINE)                         \
    {                                                                   \
        int success = 0;                                                \
        success = __eq_int32(RES, EXP);                                 \
        if (success) {                                                  \
            TEST_PASSED_MSG(INT32_FMT_TEMPL, F_NAME, EXP, RES);         \
        } else {                                                        \
            TEST_FAILED_MSG(INT32_FMT_TEMPL, F_NAME, LINE, EXP, RES);   \
            abort();                                                    \
        }                                                               \
    }

#define ASSERT_NE_INT32(RES, EXP, F_NAME, LINE)                         \
    {                                                                   \
        int success = 0;                                                \
        success = __ne_int32(RES, EXP);                                 \
        if (success) {                                                  \
            TEST_PASSED_MSG(INT32_FMT_TEMPL, F_NAME, EXP, RES);         \
        } else {                                                        \
            TEST_FAILED_MSG(INT32_FMT_TEMPL, F_NAME, LINE, EXP, RES);   \
            abort();                                                    \
        }                                                               \
    }

/* will not abort() routine execution, only
 * write to stderr about test failure or success. */
#define EXPECT_EQ_INT32(RES, EXP, F_NAME, STATE, LINE)                  \
    {                                                                   \
        int success = 0;                                                \
        success = __eq_int32(RES, EXP);                                 \
        if (success) {                                                  \
            TEST_PASSED_MSG(INT32_FMT_TEMPL, F_NAME, EXP, RES);         \
        } else {                                                        \
            TEST_FAILED_MSG(INT32_FMT_TEMPL, F_NAME, LINE, EXP, RES);   \
        }                                                               \
        *STATE = success;                                               \
    }

#define EXPECT_NE_INT32(RES, EXP, F_NAME, STATE, LINE)                  \
    {                                                                   \
        int success = 0;                                                \
        success = __ne_int32(RES, EXP);                                 \
        if (success) {                                                  \
            TEST_PASSED_MSG(INT32_FMT_TEMPL, F_NAME, EXP, RES);         \
        } else {                                                        \
            TEST_FAILED_MSG(INT32_FMT_TEMPL, F_NAME, LINE, EXP, RES);   \
        }                                                               \
        *STATE = success;                                               \
    }

/* assert to double */
#define ASSERT_EQ_DBL(RES, EXP, EPSILON, F_NAME, LINE)                  \
    {                                                                   \
        int success = 0;                                                \
        success = __eq_double64(RES, EXP, EPSILON);                     \
        if (success) {                                                  \
            TEST_PASSED_MSG(DBL_FMT_TEMPL, F_NAME, EXP, RES);           \
        } else {                                                        \
            TEST_FAILED_MSG(DBL_FMT_TEMPL, F_NAME, LINE, EXP, RES);     \
            abort();                                                    \
        }                                                               \
    }

#define ASSERT_NE_DBL(RES, EXP, EPSILON, F_NAME, LINE)                  \
    {                                                                   \
        int success = 0;                                                \
        success = __ne_double64(RES, EXP, EPSILON);                     \
        if (success) {                                                  \
            TEST_PASSED_MSG(DBL_FMT_TEMPL, F_NAME, EXP, RES);           \
        } else {                                                        \
            TEST_FAILED_MSG(DBL_FMT_TEMPL, F_NAME, LINE, EXP, RES);     \
            abort();                                                    \
        }                                                               \
    }

/* EXPECT waiting for pointer for test result */
#define EXPECT_EQ_DBL(RES, EXP, STATE, EPSILON, F_NAME, LINE)           \
    {                                                                   \
        int success = 0;                                                \
        success = __eq_double64(RES, EXP, EPSILON);                     \
        if (success) {                                                  \
            TEST_PASSED_MSG(DBL_FMT_TEMPL, F_NAME, EXP, RES);           \
        } else {                                                        \
            TEST_FAILED_MSG(DBL_FMT_TEMPL, F_NAME, LINE, EXP, RES);     \
        }                                                               \
        *STATE = success;                                               \
    }

#define EXPECT_NE_DBL(RES, EXP, STATE, EPSILON, F_NAME, LINE)           \
    {                                                                   \
        int success = 0;                                                \
        success = __ne_double64(RES, EXP, EPSILON);                     \
        if (success) {                                                  \
            TEST_PASSED_MSG(DBL_FMT_TEMPL, F_NAME, EXP, RES);           \
        } else {                                                        \
            TEST_FAILED_MSG(DBL_FMT_TEMPL, F_NAME, LINE, EXP, RES);     \
        }                                                               \
        *STATE = success;                                               \
    }

#endif /* _M_ASSERT_H */
