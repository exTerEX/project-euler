#include <stdio.h>
#include <stdint.h>

int main() {
    int64_t total = 0;
    for (int N = 1; N <= 100; N++) {
        int64_t c8 = 1;
        for (int k = 1; k <= 8; k++) c8 = c8 * (N + k) / k;
        int64_t c9 = 1;
        for (int k = 1; k <= 9; k++) c9 = c9 * (N + k) / k;
        total += c8 + (c9 - 1) - 9;
    }
    printf("%ld\n", total);
    return 0;
}
