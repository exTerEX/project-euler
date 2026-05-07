#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LIMIT 200

static uint8_t sieve[LIMIT];
static uint64_t ways[LIMIT + 1];

int main() {
    for (int i = 2; i < LIMIT; ++i) sieve[i] = 1;
    for (int i = 2; i < LIMIT; ++i) {
        if (!sieve[i]) continue;
        for (int j = 2 * i; j < LIMIT; j += i) sieve[j] = 0;
    }

    ways[0] = 1;
    for (int p = 2; p < LIMIT; ++p) {
        if (!sieve[p]) continue;
        for (int n = p; n <= LIMIT; ++n)
            ways[n] += ways[n - p];
    }

    for (int n = 2; n <= LIMIT; ++n) {
        if (ways[n] > 5000) {
            printf("%d\n", n);
            return 0;
        }
    }

    return 0;
}
