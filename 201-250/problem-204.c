#include <stdint.h>
#include <stdio.h>

static uint32_t primes[64];
static int prime_n = 0;
static uint64_t limit = 1000000000ULL;

static void sieve_primes(uint32_t maxp) {
    for (uint32_t i = 2; i <= maxp; i++) {
        int ok = 1;
        for (int j = 0; j < prime_n; j++) {
            uint32_t p = primes[j];
            if ((uint64_t)p * p > i) {
                break;
            }
            if (i % p == 0) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            primes[prime_n++] = i;
        }
    }
}

static uint64_t dfs(uint64_t value, int from) {
    uint64_t count = 1;
    for (int i = from; i < prime_n; i++) {
        uint64_t next = value * primes[i];
        if (next > limit) {
            break;
        }
        count += dfs(next, i);
    }
    return count;
}

int main(void) {
    sieve_primes(100);
    printf("%llu\n", (unsigned long long)dfs(1, 0));
    return 0;
}
