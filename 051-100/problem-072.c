#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define LIMIT 1000000

int main() {
    uint32_t* phi = calloc(LIMIT + 1, sizeof(uint32_t));

    for (uint32_t i = 0; i <= LIMIT; ++i) phi[i] = i;
    for (uint32_t p = 2; p <= LIMIT; ++p) {
        if (phi[p] == p) {
            for (uint32_t j = p; j <= LIMIT; j += p)
                phi[j] -= phi[j] / p;
        }
    }

    uint64_t sum = 0;
    for (uint32_t i = 2; i <= LIMIT; ++i) sum += phi[i];

    free(phi);
    printf("%lu\n", sum);
    return 0;
}
