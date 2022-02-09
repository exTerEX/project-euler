#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

bool is_prime(int32_t);

int main() {
    int32_t nmax = 0, amax = 0, bmax = 0;

    for (int32_t i = -999; i < 1000; i++) {
        for (int32_t j = -999; j < 1000; j++) {
            uint32_t n;

            for (n = 0; is_prime(n * n + i * n + j); n++);

            if (n > nmax) { nmax = n; amax = i; bmax = j; }
        }
    }

    printf("%d\n", amax * bmax);

    return 0;
}

bool is_prime(int32_t n) {
    if (n <= 1) { return 0; }

    if (n == 2) { return 1; }

    for (uint32_t i = 2; i < sqrt((double)n); i++) {
        if (n % i == 0) { return false; }
    }

    return true;
}
