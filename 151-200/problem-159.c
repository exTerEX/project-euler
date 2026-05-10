#include <stdint.h>
#include <stdio.h>

#define LIMIT 1000000

static int drs(int n) {
    return 1 + (n - 1) % 9;
}

int main(void) {
    static int mdrs[LIMIT];

    for (int n = 2; n < LIMIT; n++) {
        mdrs[n] = drs(n);
    }

    for (int a = 2; a < LIMIT; a++) {
        int max_b = (LIMIT - 1) / a;
        for (int b = 2; b <= max_b; b++) {
            int n = a * b;
            int candidate = mdrs[a] + mdrs[b];
            if (candidate > mdrs[n]) {
                mdrs[n] = candidate;
            }
        }
    }

    int64_t sum = 0;
    for (int n = 2; n < LIMIT; n++) {
        sum += mdrs[n];
    }

    printf("%lld\n", (long long)sum);
    return 0;
}
