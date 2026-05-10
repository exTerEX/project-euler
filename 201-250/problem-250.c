#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t powmod_u64(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if ((exp & 1U) != 0U) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1U;
    }
    return result;
}

int main(void) {
    const uint64_t modulus = 10000000000000000ULL;
    uint64_t subsets[250] = {0};
    uint64_t next[250];
    subsets[0] = 1;

    for (uint32_t i = 1; i <= 250250; ++i) {
        uint32_t offset = (uint32_t)powmod_u64(i, i, 250);
        for (uint32_t j = 0; j < 250; ++j) {
            next[j] = (subsets[j] + subsets[(j + 250 - offset) % 250]) % modulus;
        }
        for (uint32_t j = 0; j < 250; ++j) {
            subsets[j] = next[j];
        }
    }

    printf("%" PRIu64 "\n", (subsets[0] + modulus - 1) % modulus);
    return 0;
}