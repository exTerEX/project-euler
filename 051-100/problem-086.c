#include <stdio.h>
#include <stdint.h>

static uint32_t gcd(uint32_t a, uint32_t b) {
    while (b) { uint32_t t = b; b = a % b; a = t; }
    return a;
}

static int is_perfect_sq(uint64_t n) {
    uint64_t s = (uint64_t)__builtin_sqrt((double)n);
    while (s * s > n) --s;
    while ((s+1)*(s+1) <= n) ++s;
    return s * s == n;
}

int main() {
    uint32_t total = 0;
    for (uint32_t M = 1; ; ++M) {
        uint32_t count = 0;
        for (uint32_t s = 2; s <= 2 * M; ++s) {
            if (!is_perfect_sq((uint64_t)s * s + (uint64_t)M * M)) continue;
            uint32_t lo = (s > M + 1) ? s - M : 1;
            uint32_t hi = s / 2;
            if (hi >= lo) count += hi - lo + 1;
        }
        total += count;
        if (total > 1000000) {
            printf("%u\n", M);
            return 0;
        }
    }
    return 0;
}
