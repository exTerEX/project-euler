#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 1000000

uint8_t sieve[MAX];

void init_sieve();
int32_t find_longest_prime_sum();

int main() {
    init_sieve();
    printf("%d\n", find_longest_prime_sum());

    return 0;
}

void init_sieve() {
    for (int32_t i = 0; i < MAX; ++i) {
        sieve[i] = 1;
    }
    sieve[0] = sieve[1] = 0;

    for (int32_t i = 2; i < MAX; ++i) {
        if (sieve[i]) {
            for (int32_t j = 2 * i; j < MAX; j += i) { sieve[j] = 0; }
        }
    }
}

int32_t find_longest_prime_sum() {
    int32_t n_primes = 0, sum, * primes;

    for (int32_t i = 0; i < MAX; ++i) {
        if (sieve[i]) {
            ++n_primes;
        }
    }

    primes = malloc(sizeof * primes * n_primes);

    int32_t i, j;
    for (i = j = 0; i < MAX; ++i) {
        if (sieve[i]) {
            primes[j++] = i;
        }
    }

    int32_t longest_sum = 0, longest_length = 0;
    for (int32_t i = 0; i < n_primes; ++i) {
        sum = 0;

        for (int32_t j = i; j < n_primes; ++j) {
            sum += primes[j];

            if (sum > MAX) { break; }

            if (sieve[sum] && j - i > longest_length) {
                longest_length = j - i;
                longest_sum = sum;
            }
        }
    }

    return longest_sum;
}
