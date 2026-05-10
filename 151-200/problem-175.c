#include <stdint.h>
#include <stdio.h>

static uint64_t gcd64(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(void) {
    uint64_t p = 123456789ULL;
    uint64_t q = 987654321ULL;

    uint64_t g = gcd64(p, q);
    p /= g;
    q /= g;

    uint64_t a = q;
    uint64_t b = p;

    uint64_t cf[64];
    int cf_len = 0;
    while (b != 0) {
        cf[cf_len++] = a / b;
        uint64_t r = a % b;
        a = b;
        b = r;
    }

    uint64_t out[64];
    int out_len = 0;
    out[out_len++] = 1;
    out[out_len++] = cf[cf_len - 1] - 1;
    for (int i = cf_len - 2; i >= 0; i--) {
        out[out_len++] = cf[i];
    }

    for (int i = 0; i < out_len; i++) {
        if (i > 0) {
            printf(",");
        }
        printf("%llu", (unsigned long long)out[i]);
    }
    printf("\n");
    return 0;
}
