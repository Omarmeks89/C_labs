#include "../_m_assert.h"
#include "../simple_stat.h"

int test_average_valid_data_pass_s() {
    int values[] = {1, -2, 3, 4, -5, 6};
    int size = 6;
    int res = -1, exp_stat = 0;
    double _avg = 0.0;
    double exp_ = 1.166;

    res = average(values, size, &_avg);
    ASSERT_EQ_INT32(res, exp_stat, test_average_valid_data_pass, LINE());
    ASSERT_EQ_DBL(_avg, exp_, DBL_e_3, test_average_valid_data_pass, LINE());
    return 0;
}

int test_return_NULADR_s() {
    int *nulladr = NULL;
    int size = 6;
    int res = -1;
    double _avg = 0.0;

    res = average(nulladr, size, &_avg);

    /* should be NULADR here. */
    ASSERT_EQ_INT32(res, NULADR, test_return_NULADR_s, LINE());
    return 0;
}

int test_return_NULADR_on_double_s() {
    int values[] = {1, 2, 3, 4, 5, 6};
    int size = 6;
    int res = -1;

    res = average(values, size, NULL);
    ASSERT_EQ_INT32(res, NULADR, test_return_NULADR_on_double_s, LINE());
    return 0;
}

int test_return_INVDIM_on_inv_size_s() {
    int values[] = {1, 2, 3, 4, 5, 6};
    double valid_ptr = 0.0;
    int size = -6;
    int res = -1;

    res = average(values, size, &valid_ptr);
    ASSERT_EQ_INT32(res, INVDIM, test_return_INVDIM_on_inv_size_s, LINE());
    return 0;
}

int test_return_INVDIM_on_ovf_size_s() {
    int values[] = {1, 2, 3, 4, 5, 6};
    double valid_ptr = 0.0;
    int size = MAX_ARRAY_SIZE + 1;
    int res = -1;

    res = average(values, size, &valid_ptr);
    ASSERT_EQ_INT32(res, INVDIM, test_return_INVDIM_on_ovf_size_s, LINE());
    return 0;
}

int test_return_GOTOVF_underflow() {
    int values[] = {-1, -2, INT32_MIN};
    double valid_ptr = 0.0;
    int size = 3;
    int res = -1;

    res = average(values, size, &valid_ptr);
    ASSERT_EQ_INT32(res, GOTOVF, test_return_GOTOVF_underflow, LINE());
    return 0;
}

int test_return_GOTOVF_overflow() {
    int values[] = {1, 2, INT32_MAX};
    double valid_ptr = 0.0;
    int size = 3;
    int res = -1;

    res = average(values, size, &valid_ptr);
    ASSERT_EQ_INT32(res, GOTOVF, test_return_GOTOVF_overflow, LINE());
    return 0;
}

int main() {
    int res = -1;

    res = test_average_valid_data_pass_s();
    if (res != 0)
        return 1;

    res = test_return_NULADR_s();
    if (res != 0)
        return 1;

    res = test_return_NULADR_on_double_s();
    if (res != 0)
        return 1;

    res = test_return_INVDIM_on_inv_size_s();
    if (res != 0)
        return 1;

    res = test_return_INVDIM_on_ovf_size_s();
    if (res != 0)
        return 1;

    res = test_return_GOTOVF_underflow();
    if (res != 0)
        return 1;

    res = test_return_GOTOVF_overflow();
    if (res != 0)
        return 1;

    return 0;
}
