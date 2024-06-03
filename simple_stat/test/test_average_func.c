#include "../_m_assert.h"
#include "../simple_stat.h"

int test_abs_average_valid_data_pass() {
    int values[] = {1, 2, 3, 4, 5, 6};
    int size = 6;
    int res = -1, exp_stat = 0;
    double _avg = 0.0;
    double exp_ = 3.5;

    res = abs_average(values, size, &_avg);
    ASSERT_EQ_INT32(res, exp_stat, test_abs_average_valid_data_pass, LINE());
    ASSERT_EQ_DBL(_avg, exp_, DBL_e_1, test_abs_average_valid_data_pass, LINE());
    return 0;
}

int test_return_NULADR() {
    int *nulladr = NULL;
    int size = 6;
    int res = -1;
    double _avg = 0.0;

    res = abs_average(nulladr, size, &_avg);

    /* should be NULADR here. */
    ASSERT_EQ_INT32(res, NULADR, test_return_NULADR, LINE());
    return 0;
}

int test_return_NULADR_on_double() {
    int values[] = {1, 2, 3, 4, 5, 6};
    int size = 6;
    int res = -1;

    res = abs_average(values, size, NULL);
    ASSERT_EQ_INT32(res, NULADR, test_return_NULADR_on_double, LINE());
    return 0;
}

int main() {
    int res = -1;

    res = test_abs_average_valid_data_pass();
    if (res != 0)
        return 1;

    res = test_return_NULADR();
    if (res != 0)
        return 1;

    res = test_return_NULADR_on_double();
    if (res != 0)
        return 1;

    return 0;
}
