#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int64_t gcd(int64_t a, int64_t b) { return b ? gcd(b, a % b) : a; }

int main() {
    int64_t limit = 100000000LL;
    int count = 0;
    for (int64_t m = 2; m * m < limit; m++) {
        for (int64_t n = 1; n < m; n++) {
            if ((m - n) % 2 == 0) continue;
            if (gcd(m, n) != 1) continue;
            int64_t c = m * m + n * n;
            if (c >= limit) break;
            int64_t a = m * m - n * n, b = 2 * m * n;
            int64_t diff = llabs(a - b);
            if (diff > 0 && c % diff == 0)
                count += (limit - 1) / c;
        }
    }
    printf("%d\n", count);
    return 0;
}
