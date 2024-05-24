#ifndef _M_ASSERT_H
#define _M_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

/* __convert_tostr() will cast value into 
 * 'string' representaion for
 * next check */
#define __convert_tostr(x) (#x)

#define _EXPECTED(x) (EXPECTED##x)
#define _GOT(x) (GOT##x)
#define _EXPECTED_GOT(x, y) (_EXPECTED(x)##_GOT(y))

#define __cast_to_int32(x) ((int)x)
#define __cast_to_int64(x) ((long int)x)
#define __cast_to_uint64(x) ((unsigned long)x)

#define __reflect(x, _intptr) \
    { \
        char *_t = __convert_tostr(x); \
        *_intptr = __get_value_type(_t); \
    }

int __get_value_type(const char *_t);

/* ASSERT_EQ check that two args are equal
 * or will abort execution. */
#define ASSERT_EQ(RES, EXP) \
    { \
        int *_t_ptr, _v = -1, success = 0; \
        char *_test_res = _EXPECTED_GOT(EXP, RES); \
        *_t_ptr = &_v; \
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
                     printf("undefined type for '%s'\n", #EXP); \
                    abort(); \
        } \

#endif /* _M_ASSERT_H */
