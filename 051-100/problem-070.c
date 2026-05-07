#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 10000000

static int is_perm(uint32_t a, uint32_t b) {
    int ca[10] = {0}, cb[10] = {0};
    while (a) { ca[a % 10]++; a /= 10; }
    while (b) { cb[b % 10]++; b /= 10; }
    return memcmp(ca, cb, sizeof(ca)) == 0;
}

int main() {
    uint32_t *phi = calloc(LIMIT + 1, sizeof(uint32_t));
    for (uint32_t i = 0; i <= LIMIT; ++i) phi[i] = i;
    for (uint32_t p = 2; p <= LIMIT; ++p) {
        if (phi[p] == p) {
            for (uint32_t j = p; j <= LIMIT; j += p)
                phi[j] -= phi[j] / p;
        }
    }

    uint32_t best_n = 2;
    double best_ratio = (double)2 / phi[2];

    for (uint32_t n = 3; n < LIMIT; ++n) {
        if (phi[n] == 0) continue;
        double ratio = (double)n / phi[n];
        if (ratio < best_ratio && is_perm(n, phi[n])) {
            best_ratio = ratio;
            best_n = n;
        }
    }

    free(phi);
    printf("%u\n", best_n);
    return 0;
}
