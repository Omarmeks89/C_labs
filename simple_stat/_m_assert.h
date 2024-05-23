#ifndef _M_ASSERT_H
#define _M_ASSERT_H

#include <stdio.h>

#define STRLIM 512

#if !defined(_TEST_HEADER)
#   define _TEST_HEADER 1

static inline void test_header() {
    printf("========== FILE: %s ==========\n", __FILE__);
}

#else

static inline void test_header() { ; }

#endif /* _TEST_HEADER */

#define ASSERT(TYPE, RES, EXP, F_NAME, LINE) \
    { \
        TYPE _a = (TYPE) RES; \
        TYPE _b = (TYPE) EXP; \
        if (_a == _b) { \
            printf("[LINE %d] %s: PASSED. [GOT %d, EXPECT %d]\n", LINE, F_NAME, RES, EXP); \
        } \
        else { \
            printf("[LINE %d] %s: FAILED. [GOT %d, EXPECT %d]\n", LINE, F_NAME, RES, EXP); \
        } \
    }
    
#define ASSERT_STR(RES, EXP, FUNC_NAME, LINE) \
    void LINE##FUNC_NAME(const char *res, const char *exp) \
    { \
        for( ; *res, *exp; res++, exp++) { \
            if (*res != *exp) { \
                printf("[LINE %d] %s: FAILED. [GOT %d, EXPECT %d]\n", LINE, FUNC_NAME, RES, EXP); \
                break; \
            } \
        printf("[LINE %d] %s: PASSED. [GOT %d, EXPECT %d]\n", LINE, F_NAME, RES, EXP); \
        } \
    } \
    void LINE##FUNC_NAME(&res, &exp)

#endif /* _M_ASSERT_H */
