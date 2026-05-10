#include <stdint.h>
#include <stdio.h>

static uint64_t mod_pow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1ULL) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1ULL;
    }
    return result;
}

int main(void) {
    const uint64_t mod = 100000000ULL;
    const uint64_t a = 25;
    const uint64_t b = 75;
    const uint64_t c = 1984;

    const uint64_t cc1 = (c * (c - 1)) % mod;
    const uint64_t c2 = c * c;
    const uint64_t c3 = c2 * c;
    const uint64_t c4 = c3 * c;

    uint64_t A = (c - 2) * (c4 - 7 * c3 + 20 * c2 - 29 * c + 19);
    uint64_t B = (c2 - 2 * c + 3) * (c - 2) * (c - 2) * (c - 2);

    A %= mod;
    B %= mod;

    uint64_t N[26][76] = {{0}};

    for (uint64_t i = 1; i <= a; i++) {
        N[i][0] = (cc1 * mod_pow(A, i, mod)) % mod;
    }
    for (uint64_t j = 1; j <= b; j++) {
        N[0][j] = (cc1 * mod_pow(B, j, mod)) % mod;
    }

    for (uint64_t i = 1; i <= a; i++) {
        for (uint64_t j = 1; j <= b; j++) {
            uint64_t x = (N[i - 1][j] * A) % mod;
            uint64_t y = (N[i][j - 1] * B) % mod;
            N[i][j] = (x + y) % mod;
        }
    }

    printf("%llu\n", (unsigned long long)N[a][b]);
    return 0;
}
