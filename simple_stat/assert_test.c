#include <stdio.h>

#include "_m_assert.h"

int test_LINE_macro_success() {
    int exp = __LINE__, res = LINE();
    ASSERT_EQ_INT32(res, exp, LINE());
    return 0;
}

/* test that ASSERT_EQ_INT32 compare
 * numbers correct. */
int test_assert_eq_int32() {
    int exp = 10, res = 10;
    ASSERT_EQ_INT32(res, exp, LINE());
    return 0;
}

int test_expect_eq_int32() {
    int exp = 10, res = 10;
    EXPECT_EQ_INT32(res, exp, LINE());
    return 0;
}

int test_expect_eq_int32_failed() {
    int exp = 10, res = 8;
    EXPECT_EQ_INT32(res, exp, LINE());
    return 0;
}

int test_assert_eq_int32_aborted() {
    int exp = 10, res = 0;
    ASSERT_EQ_INT32(res, exp, LINE());
    printf("TEST SHOULD FAILED\n");
    return 1;
}

int main() {
    int res = 0;

    res = test_LINE_macro_success();
    if (res != 0)
        return res;

    res = test_assert_eq_int32();
    if (res != 0)
        return res;

    res = test_expect_eq_int32();
    if (res != 0)
        return res;

    /* think about another strategy here. */
    res = test_expect_eq_int32_failed();
    if (res != 0)
        return res;

    res = test_assert_eq_int32_aborted();
    if (res != 0)
        return res;

    return 0;
}
