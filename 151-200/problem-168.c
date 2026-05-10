#include <stdint.h>
#include <stdio.h>

static uint64_t pow_mod(uint64_t base, int exp, uint64_t mod) {
    uint64_t result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main(void) {
    const uint64_t MOD = 100000;
    uint64_t sum = 0;

    for (int d = 2; d <= 100; d++) {
        for (int k = 1; k <= 9; k++) {
            uint64_t den = 10U * k - 1U;
            uint64_t mod_den = den;
            uint64_t mod_q = den * MOD;

            uint64_t p_den = pow_mod(10U, d - 1, mod_den);
            uint64_t p_q = pow_mod(10U, d - 1, mod_q);

            for (int a = 1; a <= 9; a++) {
                if (d >= 3 && a < k) {
                    continue;
                }

                uint64_t term_den = (p_den + mod_den - (uint64_t)k % mod_den) % mod_den;
                if ((a * term_den) % mod_den != 0) {
                    continue;
                }

                uint64_t term_q = (p_q + mod_q - (uint64_t)k % mod_q) % mod_q;
                uint64_t numer_mod = (uint64_t)a * term_q % mod_q;
                uint64_t q_mod = (numer_mod / den) % MOD;
                uint64_t n_mod = (10U * q_mod + (uint64_t)a) % MOD;
                sum = (sum + n_mod) % MOD;
            }
        }
    }

    printf("%llu\n", (unsigned long long)sum);
    return 0;
}
