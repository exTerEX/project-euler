#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define SQRT3 1.7320508075688772935

static uint64_t gcd64(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(void) {
    const int top = 1053779;
    uint64_t count = 0;

    for (uint64_t u = 1; u < (uint64_t)(2.4 * top); u++) {
        for (uint64_t v = u / 2 + 1; v < u; v++) {
            if (gcd64(u, v) != 1) {
                continue;
            }

            uint64_t a = 2 * u * v - u * u;
            uint64_t b = 2 * u * v - v * v;
            uint64_t c = u * u + v * v - u * v;

            uint64_t g = gcd64(a, b);
            if (g > 1) {
                a /= g;
                b /= g;
                c /= g;
            }

            double r = ((double)a + (double)b - (double)c) / (2.0 * SQRT3);
            if (r < top) {
                count += (uint64_t)floor(top / r);
            } else {
                double r2 = ((double)a + (double)b - (double)c) / 12.0;
                if (r2 > top) {
                    break;
                }
            }
        }
    }

    printf("%llu\n", (unsigned long long)count);
    return 0;
}
