#include <stdlib.h>
#include <stdio.h>

#define PRIME_RANGE_LIM 1024

#define MAX_STATIC_PRIME 997
#define STATIC_PRIMES_CNT 168

static int primes[] = {
  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
  41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89,
  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
  157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
  227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
  283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
  367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433,
  439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
  509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593,
  599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
  661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
  751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827,
  829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
  919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997,
};

static int
next_static_prime (int num, int *next_p) {
    for (int i = 0; i < STATIC_PRIMES_CNT; i++) {
        if (num < primes[i]) {
            *next_p = primes[i];
            return 0;
        }
    }
    *next_p = 0;
    return 1;
}

static inline int
round_num(int num) {
    return num % 2 ? num + 1 : num;
}

static int
compute_primes(int num, int *_primes) {
    int tmp, j, c_num, pos;
    
    if (_primes == NULL) 
        exit(1);
    
    tmp = round_num(num);
    _primes[0] = tmp;
    
    for (int i = 0; i < STATIC_PRIMES_CNT; i++) {
        c_num = primes[i] * (tmp / primes[i]);
        // printf("set_fst=%d, stat_prime=%d\n", c_num, primes[i]);
        for (j = 0; j < PRIME_RANGE_LIM; ) {
            if (!_primes[j]) {
                if ((c_num + primes[i]) > num) {
                    c_num += primes[i];
                    pos = (c_num - tmp);
                    // printf("set_new=%d | pos=%d | new pos=%d\n", c_num, j, pos);
                    _primes[pos] = c_num;
                }
            }
            j += primes[i];
        }
    }
    return 0;
}

static int
get_next_prime(int num, const int *_primes) {
    if (_primes == NULL)
        exit(1);
        
    for (int i = 1; i < PRIME_RANGE_LIM; i++) {
        /* 1st num in array is always even */
        if (!_primes[i]) {
            printf("b=%d | c=%d | a=%d\n", _primes[i - 1], _primes[i], _primes[i + 1]);

            /* FIXME -> mock implementation */
            if (num < (_primes[i - 1] + 1))
                return _primes[i - 1] + 1;
        }
    }
    return 0;
}

int
next_prime (int num, int *next_p) {
    int *nums = NULL, prime = 0;

    if ((num < 2) || (next_p == NULL))
	    exit (1);

    if (num < MAX_STATIC_PRIME)
	    return next_static_prime(num, next_p);

    nums = (int *)calloc(PRIME_RANGE_LIM, sizeof(int));
    if (nums == NULL)
	    exit (1);

    compute_primes(num, nums);
    prime = get_next_prime(num, nums);
    free(nums);
    
    if (!prime)
        return 1;
    
    *next_p = prime;
    return 0;
}

int
main () {
    // 997 -> 1009 +
    // 1230 -> 1231 +
    // 9860 -> 9871 +
    // 995010 -> 995023 +
    // 20150022 -> 20150033 - (20150023)
    // 887839 -> 887849 +
    int num = 887839, next_p = 0;
    
    next_prime(num, &next_p);
    if (next_p == 0)
        exit(1);
        
    printf("prime after %d is %d\n", num, next_p);
    return 0;
}

