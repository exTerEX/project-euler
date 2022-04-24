#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define DIGITS 1000

uint32_t add_numbers(uint8_t* a, uint8_t* b, uint8_t* c, uint32_t n) {
    uint8_t carry = 0;
    uint32_t i;

    for (i = 0; i < n; i++) {
        c[i] = carry + a[i] + b[i];

        if (c[i] > 9) { carry = 1; c[i] -= 10; }
        else { carry = 0; }
    }

    while (carry != 0) {
        c[i] = carry + c[i];

        if (c[i] > 9) { carry = 1; c[i] -= 10; }
        else { carry = 0; }

        i++;
    }

    return i;
}

uint32_t print_number(unsigned char* number, int n) {
    uint32_t start_pos = n - 1;

    while (number[start_pos] == 0) { start_pos--; }

    for (int32_t i = start_pos; i >= 0; i--) { putchar(number[i] + 0x30); }

    putchar('\n');

    return 0;
}


uint32_t get_digits(uint8_t* number) {
    uint32_t digits = DIGITS;

    while (number[digits] == 0) { digits--; }

    return digits;
}

uint32_t main() {
    uint8_t fn[DIGITS + 1];
    uint8_t fn1[DIGITS + 1];
    uint8_t sum[DIGITS + 1];

    memset(fn, 0, DIGITS);
    memset(fn1, 0, DIGITS);
    memset(sum, 0, DIGITS);

    fn[0] = 1;
    fn1[1] = 1;

    uint32_t index = 1, digit_count = 1;

    do {
        digit_count = add_numbers(fn, fn1, sum, digit_count);

        if (digit_count == DIGITS) { break; }

        memcpy(fn, fn1, DIGITS);
        memcpy(fn1, sum, DIGITS);

        index++;
    } while (digit_count < DIGITS);

    print_number(sum, digit_count);

    return 0;
}
