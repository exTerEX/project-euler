#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const uint32_t limit = 40000000U;
    const uint8_t target_len = 25U;

    uint32_t *phi = (uint32_t *)malloc(((size_t)limit + 1) * sizeof(uint32_t));
    uint8_t *chain = (uint8_t *)malloc(((size_t)limit + 1) * sizeof(uint8_t));
    if (phi == NULL || chain == NULL) {
        free(phi);
        free(chain);
        return 1;
    }

    for (uint32_t i = 0; i <= limit; i++) {
        phi[i] = i;
    }

    for (uint32_t p = 2; p <= limit; p++) {
        if (phi[p] != p) {
            continue;
        }
        for (uint32_t j = p; j <= limit; j += p) {
            phi[j] -= phi[j] / p;
        }
    }

    chain[1] = 1;
    for (uint32_t i = 2; i <= limit; i++) {
        chain[i] = (uint8_t)(chain[phi[i]] + 1U);
    }

    uint64_t sum = 0;
    for (uint32_t p = 2; p <= limit; p++) {
        if (phi[p] == p - 1U && chain[p] == target_len) {
            sum += p;
        }
    }

    free(phi);
    free(chain);

    printf("%llu\n", (unsigned long long)sum);
    return 0;
}
