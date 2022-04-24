#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LEN 50
#define MAX 30

void multiply(uint8_t*, int32_t);
int32_t n_digits(uint8_t*);

int main() {
    uint8_t ar[LEN] = { 0 };
    int32_t n, power, answer = 0;

    for (n = 1; n < MAX; ++n) {
        memset(ar, 0, LEN * sizeof * ar);
        ar[0] = 1;

        for (power = 1; power < MAX; ++power) {
            multiply(ar, n);
            if (n_digits(ar) == power)
                ++answer;
        }
    }

    printf("%d\n", answer);
    return 0;
}

void multiply(uint8_t* digits, int32_t m)
{
    int32_t carry = 0;

    for (int32_t i = 0; i < LEN; ++i) {
        carry = digits[i] * m + carry;
        digits[i] = carry % 10;
        carry /= 10;
    }
}

int32_t n_digits(uint8_t* digits) {
    int32_t i;

    for (i = LEN - 1; digits[i] == 0; --i) { ; }

    return i + 1;
}
