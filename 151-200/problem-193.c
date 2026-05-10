#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const uint64_t n = (1ULL << 50) - 1ULL;
    const uint32_t limit = (uint32_t)sqrt((long double)n);

    int8_t *mu = (int8_t *)malloc((size_t)limit + 1);
    uint8_t *is_composite = (uint8_t *)calloc((size_t)limit + 1, 1);
    if (mu == NULL || is_composite == NULL) {
        free(mu);
        free(is_composite);
        return 1;
    }

    for (uint32_t i = 0; i <= limit; i++) {
        mu[i] = 1;
    }
    mu[0] = 0;

    for (uint32_t i = 2; (uint64_t)i * i <= limit; i++) {
        if (is_composite[i]) {
            continue;
        }
        for (uint32_t j = i * i; j <= limit; j += i) {
            is_composite[j] = 1;
        }
    }

    for (uint32_t p = 2; p <= limit; p++) {
        if (is_composite[p]) {
            continue;
        }

        for (uint32_t j = p; j <= limit; j += p) {
            mu[j] = (int8_t)(-mu[j]);
        }

        uint64_t p2 = (uint64_t)p * p;
        if (p2 <= limit) {
            for (uint64_t j = p2; j <= limit; j += p2) {
                mu[j] = 0;
            }
        }
    }

    int64_t answer = 0;
    for (uint64_t k = 1; k <= limit; k++) {
        int8_t mk = mu[k];
        if (mk == 0) {
            continue;
        }
        answer += (int64_t)mk * (int64_t)(n / (k * k));
    }

    free(mu);
    free(is_composite);
    printf("%lld\n", (long long)answer);
    return 0;
}
