#include <stdio.h>
#include <stdint.h>

static uint32_t gcd(uint32_t a, uint32_t b) {
    while (b) { uint32_t t = b; b = a % b; a = t; }
    return a;
}

int main() {
    uint64_t count = 0;

    for (uint32_t d = 2; d <= 12000; ++d) {
        uint32_t pmin = d / 3 + 1;
        uint32_t pmax = (d - 1) / 2;
        for (uint32_t p = pmin; p <= pmax; ++p) {
            if (3 * p > d && gcd(p, d) == 1) ++count;
        }
    }

    printf("%lu\n", count);
    return 0;
}
