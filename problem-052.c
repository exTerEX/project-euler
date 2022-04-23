#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool is_permutation(int32_t, int32_t);

int32_t main() {
    for (int32_t n = 1; ; ++n)
        if (is_permutation(n, 2 * n)
            && is_permutation(n, 3 * n)
            && is_permutation(n, 4 * n)
            && is_permutation(n, 5 * n)
            && is_permutation(n, 6 * n)) {
            printf("%d\n", n);
            break;
        }

    return 0;
}

bool is_permutation(int32_t n, int32_t m) {
    uint8_t nth_digit[10] = { 0 }, mth_digit[10] = { 0 };

    while (n > 0) {
        ++nth_digit[n % 10];
        n /= 10;
    }

    while (m > 0) {
        ++mth_digit[m % 10];
        m /= 10;
    }

    for (uint8_t i = 0; i < 10; ++i) {
        if (nth_digit[i] != mth_digit[i]) { return 0; }
    }

    return 1;
}
