#include <stdint.h>
#include <stdio.h>

#define B 60
#define W 40

static uint64_t dp[B + 1][W + 1];

int main(void) {
    for (int i = 0; i <= B; i++) {
        for (int j = 0; j <= W; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;
    for (int b = 0; b <= B; b++) {
        for (int w = 0; w <= W; w++) {
            if (b + w == 0) {
                continue;
            }
            for (int i = b; i <= B; i++) {
                for (int j = w; j <= W; j++) {
                    dp[i][j] += dp[i - b][j - w];
                }
            }
        }
    }

    printf("%llu\n", (unsigned long long)dp[B][W]);
    return 0;
}
