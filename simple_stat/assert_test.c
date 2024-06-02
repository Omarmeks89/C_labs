#include <stdio.h>

#include "_m_assert.h"

int test_LINE_macro_success() {
    int exp = __LINE__, res = LINE();
    ASSERT_EQ_INT32(res, exp, test_LINE_macro_success, LINE());
    return 1;
}

/* test that ASSERT_EQ_INT32 compare
 * numbers correct. */
int test_assert_eq_int32() {
    int exp = 10, res = 10;
    ASSERT_EQ_INT32(res, exp, test_assert_eq_int32, LINE());
    return 1;
}

int test_expect_eq_int32() {
    int exp = 10, res = 10, state = 0;
    EXPECT_EQ_INT32(res, exp, test_expect_eq_int32, &state, LINE());
    return state;
}

int test_expect_ne_int32_passed() {
    int exp = 10, res = 8, state = 0;
    EXPECT_NE_INT32(res, exp, test_expect_ne_int32_passed, &state, LINE());
    return state;
}

int test_expect_ne_int32_failed() {
    int exp = 10, res = 10, state = 0;
    EXPECT_NE_INT32(res, exp, test_expect_ne_int32_failed, &state, LINE());
    return state;
}

int test_assert_ne_int32_passed() {
    int exp = 10, res = 0;
    ASSERT_NE_INT32(res, exp, test_assert_ne_int32_passed, LINE());
    return 1;
}

int test_assert_ne_int32_failed() {
    int exp = 10, res = 10;
    ASSERT_NE_INT32(res, exp, test_assert_ne_int32_failed, LINE());
    return 0;
}

int main() {
    int res = -1;

    res = test_LINE_macro_success();
    if (res == 0)
        return res;

    res = test_assert_eq_int32();
    if (res == 0)
        return res;

    res = test_expect_eq_int32();
    if (res == 0)
        return res;

    res = test_expect_ne_int32_passed();
    if (res == 0)
        return res;

    res = test_assert_ne_int32_passed();
    if (res == 0) {
        return res;
    }

    test_expect_ne_int32_failed();
    test_assert_ne_int32_failed();
    return 0;
}
