#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define MAX 1000000

float phi(int32_t);

int main() {
    int32_t max_val = -1;
    float max_ratio = 0.0;

    for (int32_t n = 2; n < MAX; ++n) {
        int32_t p = phi(n);

        if ((float)n / p > max_ratio) {
            max_ratio = (float)n / p;
            max_val = n;
        }
    }

    printf("%d\n", max_val);
    return 0;
}

float phi(int32_t n) {
    float result = (float)n;

    for (int32_t p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            result *= (1.0 - 1.0 / p);
            while (n % p == 0) { n /= p; }
        }
    }

    if (n > 1) { result *= (1.0 - 1.0 / n); }

    return result;
}
