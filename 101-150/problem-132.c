#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool is_prime(int64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

int64_t powmod(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (__int128)result * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    int64_t exponent = 1000000000LL;
    int64_t sum = 0;
    int count = 0;
    for (int64_t p = 2; count < 40; p++) {
        if (!is_prime(p)) continue;
        if (p == 2 || p == 5) continue;
        if (powmod(10, exponent, p) == 1) {
            sum += p;
            count++;
        }
    }
    printf("%ld\n", sum);
    return 0;
}
