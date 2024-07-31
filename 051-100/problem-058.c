#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX 1000000

int8_t sieve[MAX];

void init_sieve();
bool is_prime(int64_t);
int64_t n_primes_corners(int64_t len);

int main() {
    init_sieve();

    int32_t i = 3, total_primes = 0;
    for (; ; i += 2) {
        total_primes += n_primes_corners(i);
        float ratio = total_primes / (float)(2 * i - 1);
        if (ratio < 0.10f) { break; }
    }

    printf("%d\n", i);
    return 0;
}

void init_sieve() {
    for (int32_t i = 0; i < MAX; ++i) {
        sieve[i] = 1;
    }
    sieve[0] = sieve[1] = 0;

    for (int32_t i = 2; i < MAX; ++i) {
        if (sieve[i]) {
            for (int32_t j = 2 * i; j < MAX; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

bool is_prime(int64_t n) {
    if (n < MAX) { return sieve[n]; }

    for (int64_t p = 2; p * p <= n; ++p) {
        if (sieve[p] && n % p == 0) {
            return false;
        }
    }

    return true;
}

int64_t n_primes_corners(int64_t len) {
    int64_t i = 0, n = len * len;

    n -= (len - 1);
    if (is_prime(n)) {
        ++i;
    }

    n -= (len - 1);
    if (is_prime(n)) {
        ++i;
    }

    n -= (len - 1);
    if (is_prime(n)) {
        ++i;
    }

    return i;
}
