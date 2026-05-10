#include <stdio.h>
#include <stdint.h>

int main() {
    int M = 50;
    int64_t limit = 1000000;
    int64_t f[300];
    f[0] = 1;
    for (int n = 1; n < 300; n++) {
        f[n] = f[n - 1];
        for (int k = M; k <= n; k++) {
            if (n - k == 0) f[n]++;
            else f[n] += f[n - k - 1];
        }
        if (f[n] > limit) {
            printf("%d\n", n);
            return 0;
        }
    }
    return 0;
}
