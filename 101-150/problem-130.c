#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int64_t gcd(int64_t a, int64_t b) { return b ? gcd(b, a%b) : a; }

bool is_prime(int64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i+2) == 0) return false;
    return true;
}

int64_t compute_A(int64_t n) {
    int64_t r = 0;
    for (int64_t k = 1; k <= n; k++) {
        r = (r * 10 + 1) % n;
        if (r == 0) return k;
    }
    return -1;
}

int main() {
    int64_t sum = 0;
    int count = 0;
    for (int64_t n = 3; count < 25; n++) {
        if (gcd(n, 10) != 1 || is_prime(n)) continue;
        int64_t A = compute_A(n);
        if (A > 0 && (n - 1) % A == 0) {
            sum += n;
            count++;
        }
    }
    printf("%ld\n", sum);
    return 0;
}
