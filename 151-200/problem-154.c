#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LAYER 200000

static uint32_t sum2[LAYER + 1];
static uint32_t sum5[LAYER + 1];

static inline uint32_t choose_exp(const uint32_t *sums, uint32_t n, uint32_t k) {
    return sums[n] - sums[n - k] - sums[k];
}

int main(void) {
    sum2[0] = 0;
    sum5[0] = 0;

    for (uint32_t x = 1; x <= LAYER; x++) {
        uint32_t c2 = 0;
        uint32_t c5 = 0;
        uint32_t t = x;
        while ((t % 2U) == 0U) {
            t /= 2U;
            c2++;
        }
        while ((t % 5U) == 0U) {
            t /= 5U;
            c5++;
        }
        sum2[x] = sum2[x - 1] + c2;
        sum5[x] = sum5[x - 1] + c5;
    }

    uint64_t answer = 0;
    for (uint32_t i = 0; i <= LAYER; i++) {
        uint32_t e2 = choose_exp(sum2, LAYER, i);
        uint32_t e5 = choose_exp(sum5, LAYER, i);

        if (e2 >= 12U && e5 >= 12U) {
            answer += (uint64_t)i + 1ULL;
            continue;
        }

        uint32_t half = (i + 1U) / 2U;
        for (uint32_t j = 0; j <= half; j++) {
            uint32_t t2 = e2 + choose_exp(sum2, i, j);
            if (t2 < 12U) {
                continue;
            }

            uint32_t t5 = e5 + choose_exp(sum5, i, j);
            if (t5 < 12U) {
                continue;
            }

            answer++;
            if (j < i / 2U) {
                answer++;
            }
        }
    }

    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
