#include <stdio.h>
#include <stdint.h>

#define MAX 1000000

int8_t sieve[MAX];

void init_sieve();
int32_t is_truncatable_prime(int64_t);

int main() {
    int32_t i, answer;

    init_sieve();
    for (i = 8, answer = 0; i < MAX; ++i) {
        if (is_truncatable_prime(i)) {
            answer += i;
        }
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

int32_t is_truncatable_prime(int64_t n) {
    int64_t m;
    for (m = n; m > 0; m /= 10) {
        if (!sieve[m]) { return 0; }
    }

    for (m = 1; n / m > 10; m *= 10) { ; }
    for (n %= m; n > 0; m /= 10, n %= m) {
        if (!sieve[n]) { return 0; }
    }

    return 1;
}
