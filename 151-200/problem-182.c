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
    const int64_t p = 1009;
    const int64_t q = 3643;
    const int64_t phi = (p - 1) * (q - 1);

    int64_t best = -1;
    int64_t sum = 0;

    for (int64_t e = 2; e < phi; e++) {
        if (gcd64(e, phi) != 1) {
            continue;
        }

        int64_t unconcealed = (1 + gcd64(e - 1, p - 1)) * (1 + gcd64(e - 1, q - 1));

        if (best < 0 || unconcealed < best) {
            best = unconcealed;
            sum = e;
        } else if (unconcealed == best) {
            sum += e;
        }
    }

    printf("%lld\n", (long long)sum);
    return 0;
}
