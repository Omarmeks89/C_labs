#include "../_m_assert.h"
#include "../simple_stat.h"

/* _t_compare is used for compare
 * numbers in qsort() function. */
int _t_compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int test_median_even_cnt_passed() {
    int arr[] = {2, 3, 4, 6, 7, 8};
    int size = 6;
    int res = -1;
    double median_exp = 5.0, med = 0.0;

    res = median(arr, size, &med, &_t_compare);
    ASSERT_EQ_INT32(res, SUCCESS, test_median_even_cnt_passed, LINE());
    ASSERT_EQ_DBL(med, median_exp, DBL_e_2, test_median_even_cnt_passed, LINE());
    return 0;
}

int test_median_odd_cnt_passed() {
    int arr[] = {2, 3, 4, 6, 7, 8, 9};
    int size = 7;
    int res = -1;
    double median_exp = 6.0, med = 0.0;

    res = median(arr, size, &med, &_t_compare);
    ASSERT_EQ_INT32(res, SUCCESS, test_median_odd_cnt_passed, LINE());
    ASSERT_EQ_DBL(med, median_exp, DBL_e_2, test_median_odd_cnt_passed, LINE());
    return 0;
}

int test_median_return_nuladr() {
    int *arr = NULL;
    int size = 7;
    int res = -1;
    double med = 0.0;

    res = median(arr, size, &med, &_t_compare);
    ASSERT_EQ_INT32(res, NULADR, test_median_return_nuladr, LINE());
    return 0;
}

/* FIXME: test won`t pass */
int test_median_return_nequal() {
    int n_arr[2] = {1, 2};
    int size = 1024;
    int res = -1;
    int test_state = -1;
    double med = 0.0;

    res = median(n_arr, size, &med, &_t_compare);
    EXPECT_EQ_INT32(res, NEQUAL, test_median_return_nequal, &test_state, LINE());
    return 0;
}

int main() {
    int res = -1;

    res = test_median_even_cnt_passed();
    if (res != 0)
        return 1;

    res = test_median_odd_cnt_passed();
    if (res != 0)
        return 1;

    res = test_median_return_nuladr();
    if (res != 0)
        return 1;

    res = test_median_return_nequal();
    if (res != 0)
        return 1;

    return 0;
}
