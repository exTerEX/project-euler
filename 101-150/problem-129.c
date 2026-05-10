#include <stdio.h>
#include <stdint.h>

int64_t gcd(int64_t a, int64_t b) { return b ? gcd(b, a%b) : a; }

int64_t compute_A(int64_t n) {
    int64_t r = 0;
    for (int64_t k = 1; k <= n; k++) {
        r = (r * 10 + 1) % n;
        if (r == 0) return k;
    }
    return -1;
}

int main() {
    for (int64_t n = 1000001; ; n++) {
        if (gcd(n, 10) != 1) continue;
        if (compute_A(n) > 1000000) {
            printf("%ld\n", n);
            return 0;
        }
    }
    return 0;
}
