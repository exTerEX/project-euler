#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 40
#define FULL_MASK 1023

static uint64_t dp[MAX_LEN + 1][10][1 << 10];

int main(void) {
    memset(dp, 0, sizeof(dp));

    for (int d = 1; d <= 9; d++) {
        dp[1][d][1 << d] = 1;
    }

    for (int len = 1; len < MAX_LEN; len++) {
        for (int d = 0; d <= 9; d++) {
            for (int mask = 0; mask <= FULL_MASK; mask++) {
                uint64_t ways = dp[len][d][mask];
                if (ways == 0) {
                    continue;
                }

                if (d > 0) {
                    int nd = d - 1;
                    dp[len + 1][nd][mask | (1 << nd)] += ways;
                }
                if (d < 9) {
                    int nd = d + 1;
                    dp[len + 1][nd][mask | (1 << nd)] += ways;
                }
            }
        }
    }

    uint64_t answer = 0;
    for (int len = 1; len <= MAX_LEN; len++) {
        for (int d = 0; d <= 9; d++) {
            answer += dp[len][d][FULL_MASK];
        }
    }

    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
