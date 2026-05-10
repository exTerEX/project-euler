#include <stdio.h>
#include <stdint.h>

int main() {
    int N = 50;
    int64_t f[52];
    f[0] = 1;
    for (int n = 1; n <= N; n++) {
        f[n] = f[n - 1];
        for (int k = 3; k <= n; k++) {
            if (n - k == 0) f[n]++;
            else f[n] += f[n - k - 1];
        }
    }
    printf("%ld\n", f[N]);
    return 0;
}
