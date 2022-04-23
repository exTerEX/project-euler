#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LEN 200

int32_t multiply_and_sum(int32_t*, int32_t);

int main() {
    int32_t max_sum = 0, * digits = calloc(LEN, sizeof * digits);

    for (int32_t i = 2; i < 100; ++i) {
        memset(digits, 0, LEN * sizeof * digits);
        digits[0] = 1;

        for (int32_t j = 1; j < 100; ++j) {
            int32_t tmp = multiply_and_sum(digits, i);
            if (tmp > max_sum) { max_sum = tmp; }
        }
    }

    printf("%d\n", max_sum);
    return 0;
}

int32_t multiply_and_sum(int32_t* digits, int32_t m) {
    int32_t carry = 0, sum = 0;

    for (int32_t i = 0; i < LEN; ++i) {
        carry = digits[i] * m + carry;
        digits[i] = carry % 10;
        sum += digits[i];
        carry /= 10;
    }

    return sum;
}
