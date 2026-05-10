#include <math.h>
#include <stdint.h>
#include <stdio.h>

static int gcd_int(int a, int b) {
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(void) {
    const int n = 105;
    int c[1200] = {0};

    int n2 = n * n;
    int f = 0;
    for (int i = 1; i < n; i++) {
        f += 1 + (int)sqrt((double)(n2 - 1 - i * i));
    }
    f *= 4;

    for (int i = -n + 1; i < n; i++) {
        int i2 = i * i;
        int j = 0;
        while (i2 + j * j < n2) {
            if ((i > 0 || j > 0) && gcd_int(i, j) == 1) {
                int idx = (int)sqrt((double)(n2 - 1) / (i2 + j * j));
                c[idx]++;
            }
            j++;
        }
    }

    uint64_t total = 0;
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i != j) {
                total += (uint64_t)i * j * c[i] * c[j] * (uint64_t)(f - 2 * i - 2 * j);
            } else {
                total += (uint64_t)i * i * c[i] * (c[i] - 1) * (uint64_t)(f - 4 * i) / 2;
            }
        }
    }
    total /= 3;

    printf("%llu\n", (unsigned long long)total);
    return 0;
}
