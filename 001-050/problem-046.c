#include <stdio.h>
#include <stdint.h>

#define MAX 10000

uint8_t sieve[MAX];

void init_sieve();
int32_t is_goldbach(int32_t);

int main() {
    init_sieve();
    for (int32_t i = 35; i < MAX; i += 2) {
        if (!sieve[i] && !is_goldbach(i)) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}

void init_sieve()
{
    for (uint32_t i = 0; i < MAX; ++i) {
        sieve[i] = 1;
    }
    sieve[0] = sieve[1] = 0;

    for (uint32_t i = 2; i < MAX; ++i) {
        if (sieve[i]) {
            for (uint32_t j = 2 * i; j < MAX; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int32_t is_goldbach(int32_t n) {
    int32_t i;

    for (i = 1; i * i * 2 < n; ++i) {
        if (sieve[n - i * i * 2]) {
            return 1;
        }
    }

    return 0;
}
