#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 10000

int8_t sieve[SIZE];

void init_sieve();
bool is_prime(int32_t);
int32_t concatenate(int32_t, int32_t);
bool is_prime_pair(int32_t, int32_t);

int main() {
    init_sieve();

    int8_t* pairs = calloc(SIZE * SIZE, sizeof * pairs);
    for (int32_t i = 0; i < SIZE; ++i) {
        if (!is_prime(i)) { continue; }

        for (int32_t j = i + 1; j < SIZE; ++j) {
            if (!is_prime(j)) { continue; }

            if (is_prime_pair(i, j)) { pairs[i * SIZE + j] = 1; }
        }
    }

    int32_t answer = 5 * SIZE;
    for (int32_t a = 0; a < SIZE; ++a) {
        if (!is_prime(a)) { continue; }

        for (int32_t b = a + 1; b < SIZE; ++b) {
            if (!pairs[a * SIZE + b]) { continue; }

            for (int32_t c = b + 1; c < SIZE; ++c) {
                if (!pairs[a * SIZE + c] || !pairs[b * SIZE + c]) {
                    continue;
                }

                for (int32_t d = c + 1; d < SIZE; ++d) {
                    if (!pairs[a * SIZE + d] || !pairs[b * SIZE + d]
                        || !pairs[c * SIZE + d]) {
                        continue;
                    }

                    for (int32_t e = d + 1; e < SIZE; ++e) {
                        if (!pairs[a * SIZE + e] || !pairs[b * SIZE + e]
                            || !pairs[c * SIZE + e] || !pairs[d * SIZE + e]) {
                            continue;
                        }

                        if (a + b + c + d + e < answer) {
                            answer = a + b + c + d + e;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", answer);
    return 0;
}

void init_sieve() {
    memset(sieve, 1, SIZE * sizeof sieve[0]);
    sieve[0] = sieve[1] = 0;

    for (int32_t i = 2; i < SIZE; ++i) {
        if (sieve[i]) {
            for (int32_t j = 2 * i; j < SIZE; j += i) { sieve[j] = 0; }
        }
    }
}

bool is_prime(int32_t n) {
    if (n % 2 == 0) { return 0; }

    if (n < SIZE) { return sieve[n]; }

    for (int32_t i = 3; i * i <= n; i += 2) {
        if (sieve[i] && n % i == 0) { return false; }
    }

    return true;
}

int32_t concatenate(int32_t n, int32_t m) {
    int32_t i, m_copy;
    for (i = 1, m_copy = m; m_copy > 0; i *= 10) { m_copy /= 10; }

    return n * i + m;
}

bool is_prime_pair(int32_t p1, int32_t p2) {
    return is_prime(concatenate(p1, p2)) && is_prime(concatenate(p2, p1));
}
