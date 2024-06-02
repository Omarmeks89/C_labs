#include "../_m_assert.h"
#include "../simple_stat.h"

int test_abs_average_valid_data_pass() {
    int values[] = {1, 2, 3, 4, 5, 6};
    int size = 6;
    int res = -1, exp_stat = 0;
    double _avg = 0.0;
    double exp_ = 3.5;

    res = abs_average(values, size, &_avg);
    ASSERT_EQ_INT32(res, exp_stat, abs_average, LINE());
    ASSERT_EQ_DBL(_avg, exp_, DBL_e_1, abs_average, LINE());
    return 0;
}

int main() {
    int res = -1;

    res = test_abs_average_valid_data_pass();
    if (res != 0)
        return 1;

    return 0;
}
