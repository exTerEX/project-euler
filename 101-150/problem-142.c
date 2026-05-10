#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

bool is_square(int64_t n) {
    if (n <= 0) return false;
    int64_t s = (int64_t)sqrtl((long double)n);
    while (s * s < n) s++;
    return s * s == n;
}

int main() {
    for (int64_t p = 2; ; p++) {
        for (int64_t q = (p % 2 == 0) ? 2 : 1; q < p; q += 2) {
            int64_t x = (p * p + q * q) / 2;
            int64_t y = (p * p - q * q) / 2;
            if (y <= 0) continue;
            for (int64_t r = 2; r < p; r++) {
                for (int64_t s = (r % 2 == 0) ? 2 : 1; s < r; s += 2) {
                    if ((r * r + s * s) / 2 != x) continue;
                    int64_t z = (r * r - s * s) / 2;
                    if (z <= 0 || z >= y) continue;
                    if (is_square(y + z) && is_square(y - z)) {
                        printf("%ld\n", x + y + z);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}
