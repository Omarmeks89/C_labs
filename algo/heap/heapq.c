#include <stdio.h>


typedef unsigned a_size;
typedef unsigned a_pos;

#define MIN_(a, b) (a > b ? b : a)
#define MAX_(a, b) (a > b ? a : b)
#define ARR_POS(p) (p + 1)
#define CALC_ARR_POS(p) ((p) - ((p) % 2) / (p))
#define CALC_CH_NODE(p) (2 * (p) + 1)

static int a_pos_is_valid(a_pos pos, a_size size)
{
	return pos < size ? 1 : 0;
}


int insert(int num, int *arr, a_pos pos, a_size size)
{
	/* return 1 if success. */
	int tmp;
	unsigned i, j = 0;
	if (!a_pos_is_valid(pos, size))
		return 0;
	*(arr + (pos + 1)) = num;
	i = ARR_POS(pos + 1);
	while(arr[i - 1] > arr[MAX_(0, CALC_ARR_POS(i) - 1)]) {
		j = CALC_ARR_POS(i);
		tmp = arr[i - 1];
		arr[i - 1] = arr[j - 1];
		arr[j - 1] = tmp;
		i = j;
	}
	return 1;
}

int extract_max(int *arr, int *max_num)
{
	/* return 1 if success (arr not empty). */
	return 1;
}
