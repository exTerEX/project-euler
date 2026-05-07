#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LIMIT 1500000

static uint8_t triple_count[LIMIT + 1];

static uint32_t gcd(uint32_t a, uint32_t b) {
    while (b) { uint32_t t = b; b = a % b; a = t; }
    return a;
}

int main() {
    memset(triple_count, 0, sizeof(triple_count));

    for (uint32_t m = 2; 2 * m * (m + 1) <= LIMIT; ++m) {
        for (uint32_t n = 1; n < m; ++n) {
            if (gcd(m, n) != 1 || (m - n) % 2 == 0) continue;
            uint32_t L0 = 2 * m * (m + n);
            if (L0 > LIMIT) break;
            for (uint32_t k = L0; k <= LIMIT; k += L0) {
                if (triple_count[k] < 2) ++triple_count[k];
            }
        }
    }

    uint32_t count = 0;
    for (uint32_t L = 2; L <= LIMIT; ++L)
        if (triple_count[L] == 1) ++count;

    printf("%u\n", count);
    return 0;
}
