#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint64_t ull;

static ull mulmod(ull a, ull b, ull mod) {
    return ((unsigned __int128)a * b) % mod;
}

static ull powmod(ull base, ull exponent, ull mod) {
    ull result = 1;
    while (exponent > 0) {
        if ((exponent & 1U) != 0U) {
            result = mulmod(result, base, mod);
        }
        base = mulmod(base, base, mod);
        exponent >>= 1U;
    }
    return result;
}

static bool is_prime(ull n) {
    static const ull witnesses[] = {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL};
    static const ull small_primes[] = {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL};

    if (n < 2) {
        return false;
    }
    for (size_t i = 0; i < sizeof(small_primes) / sizeof(small_primes[0]); ++i) {
        ull prime = small_primes[i];
        if (n == prime) {
            return true;
        }
        if (n % prime == 0) {
            return false;
        }
    }

    ull d = n - 1;
    uint32_t shift = 0;
    while ((d & 1U) == 0U) {
        d >>= 1U;
        shift++;
    }

    for (size_t i = 0; i < sizeof(witnesses) / sizeof(witnesses[0]); ++i) {
        ull a = witnesses[i] % n;
        if (a == 0) {
            continue;
        }

        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }

        bool maybe_prime = false;
        for (uint32_t r = 1; r < shift; ++r) {
            x = mulmod(x, x, n);
            if (x == n - 1) {
                maybe_prime = true;
                break;
            }
            if (x == 1) {
                return false;
            }
        }

        if (!maybe_prime) {
            return false;
        }
    }

    return true;
}

static uint32_t *build_small_primes(uint32_t limit, size_t *count) {
    uint8_t *composite = calloc(limit + 1U, sizeof(uint8_t));
    uint32_t *primes = malloc((limit + 1U) * sizeof(uint32_t));
    if (composite == NULL || primes == NULL) {
        free(composite);
        free(primes);
        return NULL;
    }

    *count = 0;
    for (uint32_t p = 2; p <= limit; ++p) {
        if (composite[p]) {
            continue;
        }
        primes[(*count)++] = p;
        if ((ull)p * p > limit) {
            continue;
        }
        for (uint32_t multiple = p * p; multiple <= limit; multiple += p) {
            composite[multiple] = 1;
        }
    }

    free(composite);
    return primes;
}

static uint32_t solve(uint32_t limit) {
    const uint32_t max_sieve_prime = (limit / 50U > 10000U) ? (limit / 50U) : 10000U;
    const uint32_t filter_threshold = 2U * max_sieve_prime;
    size_t small_prime_count = 0;
    uint32_t *small_primes = build_small_primes(max_sieve_prime, &small_prime_count);
    uint8_t *candidate = malloc((size_t)limit + 1U);
    uint32_t count = 0;

    if (small_primes == NULL || candidate == NULL) {
        free(small_primes);
        free(candidate);
        return 0;
    }

    memset(candidate, 1, (size_t)limit + 1U);
    candidate[0] = 0;
    if (limit >= 1U) {
        candidate[1] = 0;
    }

    for (ull n = 2; n <= limit; ++n) {
        if (!candidate[n]) {
            continue;
        }

        ull value = 2ULL * n * n - 1ULL;
        if (is_prime(value)) {
            count++;
            continue;
        }

        if (n < filter_threshold) {
            for (size_t i = 0; i < small_prime_count; ++i) {
                ull prime = small_primes[i];
                if (value > prime && value % prime == 0) {
                    for (ull j = n; j <= limit; j += prime) {
                        candidate[j] = 0;
                    }
                    break;
                }
            }
        }
    }

    free(small_primes);
    free(candidate);
    return count;
}

int main(void) {
    uint32_t limit = 50000000U;
    if (scanf("%u", &limit) != 1) {
        limit = 50000000U;
    }

    printf("%u\n", solve(limit));
    return 0;
}

