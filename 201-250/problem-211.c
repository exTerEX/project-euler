#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const uint32_t limit = 64000000U;

    uint32_t *spf = (uint32_t *)calloc((size_t)limit + 1, sizeof(uint32_t));
    if (spf == NULL) {
        return 1;
    }

    for (uint32_t i = 2; i <= limit; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            if ((uint64_t)i * i <= limit) {
                for (uint32_t j = i * i; j <= limit; j += i) {
                    if (spf[j] == 0) {
                        spf[j] = i;
                    }
                }
            }
        }
    }

    uint64_t sum_n = 0;

    for (uint32_t n = 1; n <= limit; n++) {
        uint32_t m = n;
        __uint128_t sigma2 = 1;

        while (m > 1) {
            uint32_t p = spf[m];
            __uint128_t p2 = (__uint128_t)p * p;
            __uint128_t term = 1;
            __uint128_t pow = 1;

            while (m % p == 0) {
                m /= p;
                pow *= p2;
                term += pow;
            }

            sigma2 *= term;
        }

        uint64_t s = (uint64_t)sigma2;
        uint64_t r = (uint64_t)sqrt((long double)s);
        while ((r + 1) * (r + 1) <= s) {
            r++;
        }
        while (r * r > s) {
            r--;
        }
        if (r * r == s) {
            sum_n += n;
        }
    }

    free(spf);
    printf("%llu\n", (unsigned long long)sum_n);
    return 0;
}
