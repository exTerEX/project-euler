#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int32_t factorial(int32_t);

int main() {
    int32_t N = 1000000 - 1, SIZE = 10, n_digit = SIZE;
    uint64_t answer = 0;
    uint8_t* digits = (uint8_t*)calloc(SIZE, sizeof(uint8_t));

    for (int32_t i = 0; i < SIZE; ++i) { digits[i] = i; }

    for (int32_t i = 1; i < SIZE; ++i) {
        int32_t d = N / factorial(SIZE - i);

        N %= factorial(SIZE - i);
        answer = answer * 10 + digits[d];

        for (int32_t j = d; j < n_digit; ++j) {
            digits[j] = digits[j + 1];
        }

        --n_digit;

        if (N == 0) { break; }
    }

    for (int32_t j = 0; j < n_digit; ++j) {
        answer = answer * 10 + digits[j];
    }

    printf("%lu\n", answer);
    free(digits);

    return 0;
}

int32_t factorial(int32_t n)
{
    int32_t p = 1;
    while (n-- > 1) {
        p *= (n + 1);
    }

    return p;
}
