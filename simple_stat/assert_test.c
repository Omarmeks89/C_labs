#include "_m_assert.h"

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

int main() {
    int res = 0;
    res = test_assert_eq_int32();
    if (res != 0)
        return res;

    res = test_expect_eq_int32();
    if (res != 0)
        return res;

    return 0;
}
