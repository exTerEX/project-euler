#include <stdio.h>
#include <stdint.h>

int main() {
    int N = 50;
    int64_t f[51];
    f[0] = 1;
    for (int i = 1; i <= N; i++) {
        f[i] = f[i - 1];
        if (i >= 2) f[i] += f[i - 2];
        if (i >= 3) f[i] += f[i - 3];
        if (i >= 4) f[i] += f[i - 4];
    }
    printf("%ld\n", f[N]);
    return 0;
}
