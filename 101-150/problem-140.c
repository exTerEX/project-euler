#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

int cmp64(const void *a, const void *b) {
    int64_t x = *(int64_t *)a, y = *(int64_t *)b;
    return (x > y) - (x < y);
}

int main() {
    int64_t results[200];
    int nr = 0;
    int64_t NMAX = 2000000;
    for (int64_t N = 1; N <= NMAX; N++) {
        int64_t disc = 5 * N * N + 14 * N + 1;
        int64_t k = (int64_t)sqrtl((long double)disc);
        if (k * k < disc) k++;
        if (k * k == disc) {
            results[nr++] = N;
            if (nr >= 200) break;
        }
    }
    qsort(results, nr, sizeof(int64_t), cmp64);
    int64_t sum = 0;
    for (int i = 0; i < 30 && i < nr; i++) sum += results[i];
    printf("%ld\n", sum);
    return 0;
}
