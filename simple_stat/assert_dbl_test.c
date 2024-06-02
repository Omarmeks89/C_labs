#include <stdio.h>
#include <float.h>

#include "_m_assert.h"

int test_assert_eq_dbl_success() {
    double exp_ = 10.0, res = 10.0;
    ASSERT_EQ_DBL(exp_, res, DBL_EPSILON, test_assert_eq_dbl_success, LINE());
    return 0;
}

int main() {
    int res = 0;

    res = test_assert_eq_dbl_success();
    if (res != 0)
        return 1;
    return 0;
}
