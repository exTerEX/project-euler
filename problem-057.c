#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LEN 400

void add(uint8_t*, uint8_t*);
int32_t n_digits(uint8_t*);

int main() {
    uint8_t* numerator = calloc(LEN, sizeof * numerator);
    uint8_t* denominator = calloc(LEN, sizeof * denominator);
    uint8_t* tmp = calloc(LEN, sizeof * tmp);

    numerator[0] = 3;
    denominator[0] = 2;
    int32_t iter = 1, answer = 0;

    while (iter++ < 1000) {
        memcpy(tmp, numerator, LEN * sizeof * tmp);
        add(numerator, denominator);
        add(numerator, denominator);
        add(denominator, tmp);

        if (n_digits(numerator) > n_digits(denominator)) {
            ++answer;
        }
    }

    printf("%d\n", answer);
    return 0;
}

void add(uint8_t* a, uint8_t* b) {
    int32_t i, carry;

    for (i = 0, carry = 0; i < LEN; ++i) {
        carry += a[i] + b[i];
        a[i] = carry % 10;
        carry /= 10;
    }
}

int32_t n_digits(uint8_t* n) {
    int32_t i = LEN - 1;
    for (; n[i] == 0 && i > 0; --i) { ; }

    return i;
}
