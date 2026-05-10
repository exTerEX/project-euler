#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static const uint64_t primes[] = {
    2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL
};

static uint64_t best = 0;
static uint64_t factors[32];
static int factors_len = 0;

static int cmp_desc(const void *pa, const void *pb) {
    uint64_t a = *(const uint64_t *)pa;
    uint64_t b = *(const uint64_t *)pb;
    if (a < b) {
        return 1;
    }
    if (a > b) {
        return -1;
    }
    return 0;
}

static void evaluate_partition(void) {
    uint64_t sorted[32];
    for (int i = 0; i < factors_len; i++) {
        sorted[i] = factors[i];
    }
    qsort(sorted, (size_t)factors_len, sizeof(uint64_t), cmp_desc);

    __uint128_t n = 2;
    for (int i = 0; i < factors_len; i++) {
        uint64_t exp = (sorted[i] - 1ULL) / 2ULL;
        for (uint64_t e = 0; e < exp; e++) {
            n *= primes[i];
            if (best != 0 && n >= best) {
                return;
            }
            if (n > UINT64_MAX) {
                return;
            }
        }
    }

    uint64_t value = (uint64_t)n;
    if (best == 0 || value < best) {
        best = value;
    }
}

static void search_partitions(uint64_t rem, uint64_t min_factor) {
    factors[factors_len++] = rem;
    evaluate_partition();
    factors_len--;

    for (uint64_t f = min_factor; f * f <= rem; f += 2ULL) {
        if (rem % f != 0) {
            continue;
        }
        factors[factors_len++] = f;
        search_partitions(rem / f, f);
        factors_len--;
    }
}

int main(void) {
    const uint64_t target = 47547ULL;
    const uint64_t d = 2ULL * target + 1ULL;

    search_partitions(d, 3ULL);
    printf("%llu\n", (unsigned long long)best);
    return 0;
}
