#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>

#define N 10000

uint32_t pentagonal(uint32_t);
int64_t is_pentagonal(int64_t);

int main() {
    unsigned min = UINT_MAX;

    for (uint32_t i = 1; i < N; i++) {
        for (uint32_t j = i; j < N; j++) {
            uint32_t k = pentagonal(i);
            uint32_t l = pentagonal(j);
            if (is_pentagonal(k + l) && is_pentagonal(l - k)) {
                if (l - k < min) {
                    min = l - k;
                }
            }
        }
    }

    printf("%u\n", min);
    return 0;
}

uint32_t pentagonal(uint32_t n) {
    return n * (3 * n - 1) / 2;
}

int64_t is_pentagonal(int64_t n) {
    unsigned sq = sqrt(1 + 24 * n);
    return sq * sq == 1 + 24 * n && (1 + sq) % 6 == 0;
}
