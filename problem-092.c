#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 10000000

int8_t arrive_at_89[MAX] = { 0 };

int32_t square_digits(int32_t);
int32_t chain_contains_89(int32_t);

int main() {
    int32_t count = 0;
    for (int32_t i = 1; i < MAX; ++i) {
        if (chain_contains_89(i)) {
            arrive_at_89[i] = 1;
            ++count;
        }
    }

    printf("%d\n", count);
    return 0;
}

int32_t chain_contains_89(int32_t n) {
    while (n != 1 && n != 89) {
        if (arrive_at_89[n]) { return 1; }
        n = square_digits(n);
    }

    return n == 89;
}

int32_t square_digits(int32_t n) {
    int32_t res = 0;
    while (n > 0) {
        res += (n % 10) * (n % 10);
        n /= 10;
    }

    return res;
}
