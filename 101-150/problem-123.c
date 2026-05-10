#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool is_prime(uint64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i+2) == 0) return false;
    return true;
}

int main() {
    uint64_t limit = 10000000000ULL;
    uint64_t p = 2;
    int n = 1;
    while (1) {
        if (n % 2 == 1) {
            __uint128_t r = ((__uint128_t)2 * n * p) % ((__uint128_t)p * p);
            if ((uint64_t)r > limit) {
                printf("%d\n", n);
                return 0;
            }
        }
        do { p++; } while (!is_prime(p));
        n++;
    }
    return 0;
}
