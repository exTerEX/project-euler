#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t phi(uint64_t value, const uint32_t *primes, uint32_t prime_count) {
    uint64_t result = value;
    uint64_t reduced = value;

    for (uint32_t i = 0; i < prime_count; ++i) {
        uint64_t prime = primes[i];
        if (prime * prime > reduced) {
            break;
        }
        if (reduced % prime != 0) {
            continue;
        }

        do {
            reduced /= prime;
        } while (reduced % prime == 0);

        result -= result / prime;
    }

    if (reduced > 1) {
        result -= result / reduced;
    }

    return result;
}

static bool fraction_is_less(uint64_t a_num, uint64_t a_den, uint64_t b_num, uint64_t b_den) {
    return a_num * b_den < b_num * a_den;
}

int main(void) {
    const uint64_t target_num = 15499;
    const uint64_t target_den = 94744;

    uint32_t primes[32];
    uint32_t prime_count = 0;
    uint64_t primorial = 1;

    for (uint32_t candidate = 2;; ++candidate) {
        bool is_prime = true;
        for (uint32_t i = 0; i < prime_count; ++i) {
            uint32_t prime = primes[i];
            if ((uint64_t)prime * prime > candidate) {
                break;
            }
            if (candidate % prime == 0) {
                is_prime = false;
                break;
            }
        }
        if (!is_prime) {
            continue;
        }

        primes[prime_count++] = candidate;
        primorial *= candidate;
        if (fraction_is_less(phi(primorial, primes, prime_count), primorial - 1, target_num, target_den)) {
            primorial /= candidate;
            break;
        }
    }

    for (uint64_t multiplier = 1;; ++multiplier) {
        uint64_t denominator = primorial * multiplier;
        if (fraction_is_less(phi(denominator, primes, prime_count), denominator - 1, target_num, target_den)) {
            printf("%" PRIu64 "\n", denominator);
            return 0;
        }
    }
}