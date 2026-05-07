#include <stdio.h>
#include <stdint.h>

int main() {
    int64_t best_diff = INT64_MAX;
    uint32_t best_area = 0;

    for (uint32_t m = 1; m <= 2000; ++m) {
        for (uint32_t n = m; n <= 2000; ++n) {
            int64_t rect = (int64_t)m * (m + 1) / 2 * n * (n + 1) / 2;
            int64_t diff = rect - 2000000;
            if (diff < 0) diff = -diff;
            if (diff < best_diff) {
                best_diff = diff;
                best_area = m * n;
            }
        }
    }

    printf("%u\n", best_area);
    return 0;
}
