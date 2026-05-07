#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main() {
    uint32_t count = 0;

    for (uint32_t n = 2; n <= 10000; ++n) {
        uint32_t a0 = (uint32_t)sqrt((double)n);
        if (a0 * a0 == n) continue;

        uint32_t m = 0, d = 1, a = a0, period = 0;
        do {
            m = d * a - m;
            d = (n - m * m) / d;
            a = (a0 + m) / d;
            ++period;
        } while (a != 2 * a0);

        if (period & 1) ++count;
    }

    printf("%u\n", count);
    return 0;
}
