#include <stdio.h>

#include "_m_assert.h"

int test_assert_eq_dbl_success() {
    double exp_ = 10.0, res = 10.0;
    ASSERT_EQ_DBL(res, exp_, DBL_e_2, test_assert_eq_dbl_success, LINE());
    return 0;
}

int test_assert_ne_dbl_passed() {
    double exp_ = 10.011, res = 10.00;
    ASSERT_NE_DBL(res, exp_, DBL_e_2, test_assert_ne_dbl_passed, LINE());
    return 0;
}

int test_expect_eq_dbl_passed() {
    double exp_ = 10.01, res = 10.01;
    int status = 0;

    EXPECT_EQ_DBL(res, exp_, &status, DBL_e_2, test_expect_eq_dbl_passed, LINE());
    return status;
}

int test_expect_ne_dbl_passed() {
    double exp_ = 10.0000010001, res = 10.000000;
    int status = 0;

    EXPECT_NE_DBL(res, exp_, &status, DBL_e_6, test_expect_ne_dbl_passed, LINE());
    return status;
}

int main() {
    int res = 0;

    /* will abort() on fail */
    test_assert_eq_dbl_success();
    test_assert_ne_dbl_passed();

    res = test_expect_eq_dbl_passed();
    if (res == 0)
        return 1;

    res = test_expect_ne_dbl_passed();
    if (res == 0)
        return 1;

    return 0;
}
