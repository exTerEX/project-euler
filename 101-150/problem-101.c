#include <math.h>
#include <stdint.h>
#include <stdio.h>

int64_t u(int64_t n);
int64_t lagrange_bop(int k);

int main() {
    int64_t sum = 0;
    for (int k = 1; k <= 10; k++) {
        int64_t bop = lagrange_bop(k);
        if (bop != u(k + 1)) sum += bop;
    }
    printf("%ld\n", sum);
    return 0;
}

int64_t u(int64_t n) {
    int64_t result = 0, power = 1;
    for (int i = 0; i <= 10; i++) {
        result += (i % 2 == 0) ? power : -power;
        power *= n;
    }
    return result;
}

int64_t lagrange_bop(int k) {
    int x = k + 1;
    long double result = 0;
    for (int i = 1; i <= k; i++) {
        long double term = (long double)u(i);
        for (int j = 1; j <= k; j++) {
            if (j != i) term *= (long double)(x - j) / (i - j);
        }
        result += term;
    }
    return (int64_t)roundl(result);
}
