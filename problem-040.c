#include <stdio.h>
#include <stdint.h>

#define MAX 1000000

int32_t nth(int32_t);

int main() {
    int32_t answer = 1;

    for (int32_t i = 1; i <= MAX; i *= 10) { answer *= nth(i); }

    printf("%d\n", answer);

    return 0;
}

int32_t nth(int32_t n) {
    int32_t block_length, digit, number, i;

    if (n < 10) { return n; }

    for (block_length = 9, digit = 1;
        n > block_length * digit;
        n -= block_length * digit, block_length *= 10, ++digit) {
        ;
    }

    number = block_length / 9 + n / digit;

    for (i = 0; i < digit - n % digit; ++i) { number /= 10; }

    return number % 10;
}
