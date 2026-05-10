#include <math.h>
#include <stdint.h>
#include <stdio.h>

static int64_t gcd64(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(void) {
    const long double euler = 2.7182818284590452353602874713527L;
    int64_t sum = 0;

    for (int64_t n = 5; n <= 10000; n++) {
        int64_t k1 = (int64_t)(n / euler);
        int64_t k2 = k1 + 1;

        long double f1 = k1 * logl((long double)n / k1);
        long double f2 = k2 * logl((long double)n / k2);
        int64_t k = (f1 >= f2) ? k1 : k2;

        int64_t d = k / gcd64(n, k);
        while ((d % 2) == 0) {
            d /= 2;
        }
        while ((d % 5) == 0) {
            d /= 5;
        }

        if (d == 1) {
            sum -= n;
        } else {
            sum += n;
        }
    }

    printf("%lld\n", (long long)sum);
    return 0;
}
