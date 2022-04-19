#include <stdio.h>
#include <stdint.h>

#define MAX 1000000

int8_t sieve[MAX];

void init_sieve();
int64_t rotate(int64_t);
int32_t is_circular(int64_t);

int32_t main(void) {
    int32_t i, answer;

    init_sieve();
    for (i = 0, answer = 0; i < MAX; ++i) {
        if (is_circular(i)) { ++answer; }
    }

    printf("%d\n", answer);
    return 0;
}

void init_sieve() {
    for (int32_t i = 0; i < MAX; ++i) { sieve[i] = 1; }
    sieve[0] = sieve[1] = 0;

    for (int32_t i = 2; i < MAX; ++i) {
        if (sieve[i]) {
            for (int32_t j = 2 * i; j < MAX; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int64_t rotate(int64_t n) {
    int32_t n_digits, m = n;

    for (n_digits = 0; m > 0; m /= 10) { ++n_digits; }
    for (m = 1; n_digits > 1; --n_digits) { m *= 10; }

    return m * (n % 10) + n / 10;
}

int32_t is_circular(int64_t n) {
    if (!sieve[n]) { return 0; }

    int64_t rotated = rotate(n);
    while (rotated != n) {
        if (!sieve[rotated]) { return 0; }
        rotated = rotate(rotated);
    }

    return 1;
}
