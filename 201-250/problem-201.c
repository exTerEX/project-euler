#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const int n = 100;
    const int choose = 50;

    int max_sum = 0;
    for (int i = n - choose + 1; i <= n; i++) {
        max_sum += i * i;
    }

    size_t rows = (size_t)(choose + 1);
    size_t cols = (size_t)(max_sum + 1);
    uint8_t *dp = (uint8_t *)calloc(rows * cols, sizeof(uint8_t));
    if (dp == NULL) {
        return 1;
    }

    #define CELL(k, s) dp[(size_t)(k) * cols + (size_t)(s)]

    CELL(0, 0) = 1;

    for (int i = 1; i <= n; i++) {
        int v = i * i;
        int upper_k = (i < choose) ? i : choose;
        for (int k = upper_k; k >= 1; k--) {
            for (int s = max_sum; s >= v; s--) {
                uint8_t ways = CELL(k - 1, s - v);
                if (ways == 0) {
                    continue;
                }
                uint8_t cur = CELL(k, s);
                uint8_t sum = (uint8_t)(cur + ways);
                CELL(k, s) = (sum > 2U) ? 2U : sum;
            }
        }
    }

    uint64_t answer = 0;
    for (int s = 0; s <= max_sum; s++) {
        if (CELL(choose, s) == 1U) {
            answer += (uint64_t)s;
        }
    }

    free(dp);
    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
