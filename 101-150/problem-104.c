#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool is_pandigital9(uint64_t n);
bool leading_pandigital(double log_fib);

int main() {
    uint64_t MOD = 1000000000ULL;
    uint64_t a = 1, b = 1;
    double log_phi = log10((1.0 + sqrt(5.0)) / 2.0);
    double log_sqrt5 = log10(sqrt(5.0));

    for (int k = 3; ; k++) {
        uint64_t c = (a + b) % MOD;
        double log_c = log_phi * k - log_sqrt5;
        if (is_pandigital9(c) && leading_pandigital(log_c)) {
            printf("%d\n", k);
            return 0;
        }
        a = b; b = c;
    }
    return 0;
}

bool is_pandigital9(uint64_t n) {
    int seen[10] = {0};
    for (int i = 0; i < 9; i++) {
        int d = n % 10;
        if (d == 0) return false;
        seen[d]++;
        if (seen[d] > 1) return false;
        n /= 10;
    }
    return true;
}

bool leading_pandigital(double log_fib) {
    double frac = log_fib - floor(log_fib);
    double leading = pow(10, frac + 8);
    return is_pandigital9((uint64_t)leading);
}
