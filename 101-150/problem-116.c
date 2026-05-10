#include <stdio.h>
#include <stdint.h>

int64_t count_ways(int N, int m) {
    int64_t f[51];
    for (int i = 0; i <= N; i++) f[i] = 1;
    for (int i = m; i <= N; i++) f[i] = f[i - 1] + f[i - m];
    return f[N];
}

int main() {
    int N = 50;
    int64_t total = (count_ways(N, 2) - 1) + (count_ways(N, 3) - 1) + (count_ways(N, 4) - 1);
    printf("%ld\n", total);
    return 0;
}
