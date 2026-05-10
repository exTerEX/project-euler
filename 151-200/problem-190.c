#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    int64_t sum = 0;

    for (int m = 2; m <= 15; m++) {
        long double prod = 1.0L;
        for (int i = 1; i <= m; i++) {
            long double x = (2.0L * i) / (m + 1.0L);
            prod *= powl(x, i);
        }
        sum += (int64_t)floorl(prod + 1e-12L);
    }

    printf("%lld\n", (long long)sum);
    return 0;
}
