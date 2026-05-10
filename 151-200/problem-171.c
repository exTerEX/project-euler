#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define DIGITS 20
#define MAX_SUM (81 * DIGITS)
#define MOD 1000000000

static uint32_t cnt[MAX_SUM + 1];
static uint32_t sumv[MAX_SUM + 1];
static uint32_t next_cnt[MAX_SUM + 1];
static uint32_t next_sumv[MAX_SUM + 1];

int main(void) {
    uint8_t is_square[MAX_SUM + 1];
    memset(is_square, 0, sizeof(is_square));
    for (int i = 0; i * i <= MAX_SUM; i++) {
        is_square[i * i] = 1;
    }

    memset(cnt, 0, sizeof(cnt));
    memset(sumv, 0, sizeof(sumv));
    cnt[0] = 1;

    for (int pos = 0; pos < DIGITS; pos++) {
        memset(next_cnt, 0, sizeof(next_cnt));
        memset(next_sumv, 0, sizeof(next_sumv));

        for (int s = 0; s <= MAX_SUM; s++) {
            uint32_t c = cnt[s];
            uint32_t sv = sumv[s];
            if (c == 0 && sv == 0) {
                continue;
            }

            for (int d = 0; d <= 9; d++) {
                int ns = s + d * d;
                next_cnt[ns] = (next_cnt[ns] + c) % MOD;

                uint64_t add = (uint64_t)sv * 10ULL + (uint64_t)c * (uint64_t)d;
                next_sumv[ns] = (uint32_t)((next_sumv[ns] + add) % MOD);
            }
        }

        memcpy(cnt, next_cnt, sizeof(cnt));
        memcpy(sumv, next_sumv, sizeof(sumv));
    }

    uint64_t answer = 0;
    for (int s = 0; s <= MAX_SUM; s++) {
        if (is_square[s]) {
            answer += sumv[s];
            answer %= MOD;
        }
    }

    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
