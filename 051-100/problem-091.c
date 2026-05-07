#include <stdio.h>
#include <stdint.h>

static uint32_t gcd(uint32_t a, uint32_t b) {
    while (b) { uint32_t t = b; b = a % b; a = t; }
    return a;
}

int main() {
    uint32_t N = 50;
    uint64_t count = (uint64_t)3 * N * N;

    for (uint32_t x = 1; x <= N; ++x) {
        for (uint32_t y = 1; y <= N; ++y) {
            uint32_t g = gcd(x, y);
            uint32_t tp = (x * g / y < (N - y) * g / x) ? x * g / y : (N - y) * g / x;
            uint32_t tm = ((N - x) * g / y < y * g / x) ? (N - x) * g / y : y * g / x;
            count += tp + tm;
        }
    }

    printf("%lu\n", count);
    return 0;
}
