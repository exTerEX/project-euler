#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define LIMIT 120001

int main() {
    static bool fermat_sum[LIMIT];
    memset(fermat_sum, 0, sizeof(fermat_sum));

    for (int a = 1; a < LIMIT; a++) {
        for (int b = a; a + b < LIMIT; b++) {
            int64_t v = (int64_t)a * a + (int64_t)a * b + (int64_t)b * b;
            int64_t c = (int64_t)sqrtl((long double)v);
            while (c * c < v) c++;
            if (c * c == v) fermat_sum[a + b] = true;
        }
    }

    static bool seen[LIMIT];
    memset(seen, 0, sizeof(seen));
    int64_t total = 0;

    for (int p = 1; p < LIMIT; p++) {
        for (int q = p; p + q < LIMIT; q++) {
            if (!fermat_sum[p + q]) continue;
            for (int r = q; p + q + r < LIMIT; r++) {
                if (!fermat_sum[p + r]) continue;
                if (!fermat_sum[q + r]) continue;
                int T = p + q + r;
                if (!seen[T]) { seen[T] = true; total += T; }
            }
        }
    }

    printf("%ld\n", total);
    return 0;
}
