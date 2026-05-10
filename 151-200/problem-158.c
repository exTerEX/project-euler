#include <stdint.h>
#include <stdio.h>

static uint64_t comb(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k > n - k) {
        k = n - k;
    }

    uint64_t result = 1;
    for (int i = 1; i <= k; i++) {
        result = result * (uint64_t)(n - k + i) / (uint64_t)i;
    }
    return result;
}

int main(void) {
    uint64_t best = 0;
    uint64_t pow2 = 1;

    for (int n = 1; n <= 26; n++) {
        pow2 <<= 1;
        uint64_t value = comb(26, n) * (pow2 - (uint64_t)n - 1ULL);
        if (value > best) {
            best = value;
        }
    }

    printf("%llu\n", (unsigned long long)best);
    return 0;
}
