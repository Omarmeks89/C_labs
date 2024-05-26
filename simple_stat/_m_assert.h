#ifndef _M_ASSERT_H
#define _M_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

/* __convert_tostr() will cast value into 
 * 'string' representaion for
 * next check */
#define __convert_tostr(x) (#x)

#define __cast_to_int32(x) ((int)x)
#define __cast_to_int64(x) ((long int)x)
#define __cast_to_uint64(x) ((unsigned long)x)

#define __reflect(x, _intptr) \
    { \
        char *_t = __convert_tostr(x); \
        *_intptr = __get_value_type(_t); \
    }

int __get_value_type(const char *_t);
int __assert_eq_int32(int a, int b);

/* use typedef -> bcs of platform depend type size */
int __assert_eq_int64(long a, long b);
int __assert_eq_uint64(unsigned long a, unsigned long b);

/* ASSERT_EQ check that two args are equal
 * or will abort execution. */
#define ASSERT_EQ(RES, EXP) \
    { \
        int *_t_ptr; \
        int _v = 1, success = 0; \
        _t_ptr = &_v; \
        __reflect(EXP, _t_ptr); \
        switch *_t_ptr { \
            case 0: \
                    success = __assert_eq_int32(__cast_to_int32(RES), \
                                                __cast_to_int32(EXP)); \
                    break; \
            case 1: \
                    success = __assert_eq_int64(__cast_to_int64(RES), \
                                                __cast_to_int64(EXP)); \
                    break; \
            case 2: \
                    success = __assert_eq_uint64(__cast_to_uint64(RES), \
                                                __cast_to_uint64(EXP)); \
                    break; \
            default: \
                     printf("impossible type for '%s'\n", #EXP); \
                    abort(); \
        } \
        if (success) { \
            printf("PASSED. [EXPECTED: %s, GOT: %s]\n", __convert_tostr(EXP), __convert_tostr(RES)); \
        } else { \
            printf("FAILED. [EXPECTED: %s, GOT: %s]\n", __convert_tostr(EXP), __convert_tostr(RES)); \
            abort(); \
        } \
    }

#endif /* _M_ASSERT_H */
