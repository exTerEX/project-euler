#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    static uint64_t dp[31][2][3];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (int day = 0; day < 30; day++) {
        for (int used_l = 0; used_l <= 1; used_l++) {
            for (int streak_a = 0; streak_a <= 2; streak_a++) {
                uint64_t ways = dp[day][used_l][streak_a];
                if (ways == 0) {
                    continue;
                }

                dp[day + 1][used_l][0] += ways;

                if (streak_a < 2) {
                    dp[day + 1][used_l][streak_a + 1] += ways;
                }

                if (used_l == 0) {
                    dp[day + 1][1][0] += ways;
                }
            }
        }
    }

    uint64_t answer = 0;
    for (int used_l = 0; used_l <= 1; used_l++) {
        for (int streak_a = 0; streak_a <= 2; streak_a++) {
            answer += dp[30][used_l][streak_a];
        }
    }

    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
