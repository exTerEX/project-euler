#include <stdint.h>
#include <stdio.h>

#define MOD 100000U

static uint32_t pow_mod(uint32_t base, uint64_t exp, uint32_t mod) {
    uint32_t result = 1;
    while (exp > 0) {
        if (exp & 1ULL) {
            result = (uint32_t)((uint64_t)result * base % mod);
        }
        base = (uint32_t)((uint64_t)base * base % mod);
        exp >>= 1;
    }
    return result;
}

static uint32_t fast_large(uint64_t limit) {
    uint64_t iterations = limit / 10;
    uint64_t twos = 0;
    uint32_t result = pow_mod(1U * 2U * 3U * 6U * 7U * 8U * 9U, iterations, MOD);

    for (uint64_t i = 0; i < iterations; i++) {
        if (twos > 100) {
            result = (uint32_t)((uint64_t)result * 4U % MOD);
        } else {
            twos += 2;
        }

        uint64_t five = i * 2 + 1;
        twos--;
        while (five % 5 == 0) {
            five /= 5;
            twos--;
        }
        result = (uint32_t)((uint64_t)result * (five % MOD) % MOD);

        uint64_t ten = i + 1;
        while (ten % 5 == 0) {
            ten /= 5;
            twos--;
        }
        result = (uint32_t)((uint64_t)result * (ten % MOD) % MOD);
    }

    while (twos-- > 0) {
        result = (uint32_t)((uint64_t)result * 2U % MOD);
    }
    return result;
}

static uint32_t simple_reduced(uint64_t limit) {
    uint64_t result = 1;
    for (uint64_t i = 1; i <= limit; i++) {
        uint64_t cur = i;
        while (cur % 5 == 0) {
            cur /= 5;
            result /= 2;
        }
        result *= (cur % MOD);
        result %= 1000000000ULL;
    }
    return (uint32_t)(result % MOD);
}

int main(void) {
    uint64_t limit = 1000000000000ULL;

    while (limit % MOD == 0) {
        limit /= 5;
    }

    uint32_t answer;
    if (limit > 2560000ULL) {
        answer = fast_large(limit);
    } else {
        answer = simple_reduced(limit);
    }

    printf("%u\n", answer);
    return 0;
}
