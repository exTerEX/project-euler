#include <stdint.h>
#include <stdio.h>

int main(void) {
    static uint64_t dp[21][10][10];

    for (int d1 = 1; d1 <= 9; d1++) {
        for (int d2 = 0; d2 <= 9; d2++) {
            dp[2][d1][d2] = 1;
        }
    }

    for (int len = 2; len < 20; len++) {
        for (int a = 0; a <= 9; a++) {
            for (int b = 0; b <= 9; b++) {
                uint64_t ways = dp[len][a][b];
                if (ways == 0) {
                    continue;
                }
                int max_d = 9 - a - b;
                if (max_d > 9) {
                    max_d = 9;
                }
                for (int d = 0; d <= max_d; d++) {
                    dp[len + 1][b][d] += ways;
                }
            }
        }
    }

    uint64_t answer = 0;
    for (int a = 0; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            answer += dp[20][a][b];
        }
    }

    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
