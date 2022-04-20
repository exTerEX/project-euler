#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX 10000

uint8_t sieve[MAX];

void init_sieve();
bool is_permutation(int32_t, int32_t);

int main() {
    init_sieve();
    for (int32_t i = 1000; i < MAX; ++i) {
        if (i == 1487) { continue; }
        if (!sieve[i]) { continue; }
        for (int32_t step = 1; i + 2 * step < MAX; ++step) {
            if (sieve[i + step]
                && sieve[i + 2 * step]
                && is_permutation(i, i + step)
                && is_permutation(i, i + 2 * step)) {
                printf("%d%d%d\n", i, i + step, i + 2 * step);
            }
        }
    }

    return 0;
}

void init_sieve() {
    for (int32_t i = 0; i < MAX; ++i) { sieve[i] = 1; }
    sieve[0] = sieve[1] = 0;

    for (int32_t i = 2; i < MAX; ++i) {
        if (sieve[i]) {
            for (int32_t j = 2 * i; j < MAX; j += i) { sieve[j] = 0; }
        }
    }
}

bool is_permutation(int32_t n, int32_t m) {
    uint8_t nth_digit[10] = { 0 }, mth_digit[10] = { 0 };

    while (n > 0) {
        ++nth_digit[n % 10];
        n /= 10;
    }

    while (m > 0) {
        ++mth_digit[m % 10];
        m /= 10;
    }

    for (uint8_t i = 0; i < 10; ++i) {
        if (nth_digit[i] != mth_digit[i]) {
            return 0;
        }
    }

    return 1;
}
