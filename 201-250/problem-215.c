#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t rows[5000];
static int row_count = 0;

static void build_rows(int width, int pos, uint32_t mask) {
    if (pos == width) {
        rows[row_count++] = mask;
        return;
    }

    int p2 = pos + 2;
    if (p2 <= width) {
        uint32_t m = mask;
        if (p2 < width) {
            m |= (1U << p2);
        }
        build_rows(width, p2, m);
    }

    int p3 = pos + 3;
    if (p3 <= width) {
        uint32_t m = mask;
        if (p3 < width) {
            m |= (1U << p3);
        }
        build_rows(width, p3, m);
    }
}

int main(void) {
    const int width = 32;
    const int height = 10;

    build_rows(width, 0, 0U);

    uint64_t *prev = (uint64_t *)malloc((size_t)row_count * sizeof(uint64_t));
    uint64_t *next = (uint64_t *)malloc((size_t)row_count * sizeof(uint64_t));
    if (prev == NULL || next == NULL) {
        free(prev);
        free(next);
        return 1;
    }

    for (int i = 0; i < row_count; i++) {
        prev[i] = 1ULL;
    }

    for (int h = 1; h < height; h++) {
        for (int i = 0; i < row_count; i++) {
            next[i] = 0ULL;
        }

        for (int i = 0; i < row_count; i++) {
            uint32_t m1 = rows[i];
            uint64_t ways = prev[i];
            if (ways == 0) {
                continue;
            }
            for (int j = 0; j < row_count; j++) {
                if ((m1 & rows[j]) == 0U) {
                    next[j] += ways;
                }
            }
        }

        for (int i = 0; i < row_count; i++) {
            prev[i] = next[i];
        }
    }

    uint64_t answer = 0;
    for (int i = 0; i < row_count; i++) {
        answer += prev[i];
    }

    free(prev);
    free(next);

    printf("%llu\n", (unsigned long long)answer);
    return 0;
}
