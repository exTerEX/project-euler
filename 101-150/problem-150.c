#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ROWS 1000
#define TOTAL (ROWS * (ROWS + 1) / 2)

int main() {
    int32_t *t = malloc(TOTAL * sizeof(int32_t));

    uint32_t s = 0;
    for (int k = 0; k < TOTAL; k++) {
        s = (615949u * s + 797807u) & ((1u << 20) - 1);
        t[k] = (int32_t)s - (1 << 19);
    }

    int64_t **psum = malloc(ROWS * sizeof(int64_t *));
    for (int r = 0; r < ROWS; r++) {
        psum[r] = malloc((r + 2) * sizeof(int64_t));
        psum[r][0] = 0;
        int32_t *row_r = t + (int64_t)r * (r + 1) / 2;
        for (int c = 0; c <= r; c++) psum[r][c + 1] = psum[r][c] + row_r[c];
    }

    int64_t min_sum = 0;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c <= r; c++) {
            int64_t sum = 0;
            for (int d = 0; r + d < ROWS; d++) {
                sum += psum[r + d][c + d + 1] - psum[r + d][c];
                if (sum < min_sum) min_sum = sum;
            }
        }
    }

    printf("%ld\n", min_sum);

    for (int r = 0; r < ROWS; r++) free(psum[r]);
    free(psum);
    free(t);
    return 0;
}
