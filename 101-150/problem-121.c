#include <stdio.h>
#include <stdint.h>

int main() {
    int N = 15;

    int64_t dp[16][16];
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++)
            dp[i][j] = 0;
    dp[0][0] = 1;
    for (int k = 1; k <= N; k++) {
        for (int b = 0; b <= k; b++) {
            dp[k][b] = 0;
            if (b > 0) dp[k][b] += dp[k-1][b-1] * 1;
            dp[k][b] += dp[k-1][b] * k;
        }
    }

    int64_t total = 1;
    for (int k = 1; k <= N; k++) total *= (k + 1);

    int64_t win = 0;
    for (int b = N/2 + 1; b <= N; b++) win += dp[N][b];

    printf("%ld\n", total / win);
    return 0;
}
