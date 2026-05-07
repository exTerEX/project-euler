#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define KMAX 12001

static uint32_t min_n[KMAX];

static void dfs(uint32_t N, uint32_t remaining, uint32_t factor_start,
                uint32_t sum, uint32_t count) {
    int k = (int)N - (int)(sum + remaining) + (int)count + 1;
    if (k >= 2 && k < KMAX && N < min_n[k]) min_n[k] = N;

    for (uint32_t f = factor_start; (uint64_t)f * f <= remaining; ++f) {
        if (remaining % f == 0)
            dfs(N, remaining / f, f, sum + f, count + 1);
    }
}

int main() {
    for (int k = 0; k < KMAX; ++k) min_n[k] = 2 * KMAX;

    for (uint32_t n = 4; n <= 2 * KMAX; ++n)
        dfs(n, n, 2, 0, 0);

    uint8_t counted[2 * KMAX + 1];
    memset(counted, 0, sizeof(counted));
    uint64_t sum = 0;
    for (int k = 2; k < KMAX; ++k) {
        if (!counted[min_n[k]]) {
            counted[min_n[k]] = 1;
            sum += min_n[k];
        }
    }
    printf("%lu\n", sum);
    return 0;
}
