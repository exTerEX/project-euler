#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 40
#define MAX 10000

bool is_palindrom(uint8_t*, int32_t);
int32_t sum_reverse(uint8_t*, uint8_t*, int32_t);
int32_t is_lychrel(int32_t);

int main() {
    int32_t answer = 0;
    for (int32_t i = 0; i < MAX; ++i) {
        if (!is_lychrel(i)) { ++answer; }
    }

    printf("%d\n", answer);
    return 0;
}

bool is_palindrom(uint8_t* ar, int32_t len) {
    for (int32_t i = 0; i <= len / 2; ++i) {
        if (ar[i] != ar[len - 1 - i]) {
            return false;
        }
    }

    return true;
}

int32_t sum_reverse(uint8_t* ar, uint8_t* sum, int32_t len) {
    int32_t carry, i;
    for (i = 0, carry = 0; i < len; ++i) {
        carry += ar[i] + ar[len - 1 - i];
        sum[i] = carry % 10;
        carry /= 10;
    }

    while (carry > 0) {
        sum[i++] = carry % 10;
        carry /= 10;
    }

    return i;
}

int32_t is_lychrel(int32_t n) {
    uint8_t digits[SIZE] = { 0 }, sum[SIZE] = { 0 };

    int32_t i;
    for (i = 0; n > 0; ++i) {
        digits[i] = n % 10;
        n /= 10;
    }

    for (int32_t n_iter = 0; n_iter < 50; ++n_iter) {
        i = sum_reverse(digits, sum, i);

        if (is_palindrom(sum, i)) { return 1; }

        memcpy(digits, sum, i * sizeof(uint8_t));
        memset(sum, 0, i * sizeof(uint8_t));
    }

    return 0;
}
