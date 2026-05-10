#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    SLICE_SIZE = 1000000,
    MASK_ONE = 1 << 0,
    MASK_TWO = 1 << 1,
    MASK_THREE = 1 << 2,
    MASK_SEVEN = 1 << 3,
    MASK_ALL = MASK_ONE | MASK_TWO | MASK_THREE | MASK_SEVEN,
};

int main(void) {
    const uint32_t limit = 2000000000U;
    uint32_t count = 0;
    uint8_t *used = calloc(SLICE_SIZE, sizeof(uint8_t));
    if (used == NULL) {
        return 1;
    }

    const uint32_t max_a = (uint32_t)sqrt((double)limit);
    uint32_t *b1 = malloc((max_a + 1) * sizeof(uint32_t));
    uint32_t *b2 = malloc((max_a + 1) * sizeof(uint32_t));
    uint32_t *b3 = malloc((max_a + 1) * sizeof(uint32_t));
    uint32_t *b7 = malloc((max_a + 1) * sizeof(uint32_t));
    if (b1 == NULL || b2 == NULL || b3 == NULL || b7 == NULL) {
        free(used);
        free(b1);
        free(b2);
        free(b3);
        free(b7);
        return 1;
    }

    for (uint32_t a = 0; a <= max_a; ++a) {
        b1[a] = 1;
        b2[a] = 1;
        b3[a] = 1;
        b7[a] = 1;
    }

    uint32_t from = 0;
    while (from < limit) {
        uint32_t to = from + SLICE_SIZE;
        if (to > limit) {
            to = limit;
        }

        for (uint32_t a = 1; (uint64_t)a * a + (uint64_t)b1[a] * b1[a] < to; ++a) {
            uint64_t a2 = (uint64_t)a * a;

            uint32_t b = b1[a];
            for (; a2 + (uint64_t)b * b < to; ++b) {
                used[a2 + (uint64_t)b * b - from] |= MASK_ONE;
            }
            b1[a] = b;

            b = b2[a];
            for (; a2 + 2ULL * b * b < to; ++b) {
                used[a2 + 2ULL * b * b - from] |= MASK_TWO;
            }
            b2[a] = b;

            b = b3[a];
            for (; a2 + 3ULL * b * b < to; ++b) {
                used[a2 + 3ULL * b * b - from] |= MASK_THREE;
            }
            b3[a] = b;

            b = b7[a];
            for (; a2 + 7ULL * b * b < to; ++b) {
                used[a2 + 7ULL * b * b - from] |= MASK_SEVEN;
            }
            b7[a] = b;
        }

        for (uint32_t i = 0; i < to - from; ++i) {
            if (used[i] == MASK_ALL) {
                count++;
            }
            used[i] = 0;
        }

        from = to;
    }

    printf("%u\n", count);

    free(used);
    free(b1);
    free(b2);
    free(b3);
    free(b7);
    return 0;
}