#include <stdio.h>
#include <stdint.h>

int64_t count_grid(int m, int n) {
    int64_t total = (int64_t)m * (m + 1) / 2 * ((int64_t)n * (n + 1) / 2);

    for (int a = 1; a < m + n; a++) {
        for (int b = 1; a + b <= m + n; b++) {
            int cx = m - a - b + 1;
            int cy = n - a - b + 1;
            if (cx > 0 && cy > 0) total += (int64_t)cx * cy;
        }
    }
    return total;
}

int main() {
    int64_t total = 0;
    for (int m = 1; m <= 47; m++)
        for (int n = 1; n <= 43; n++)
            total += count_grid(m, n);
    printf("%ld\n", total);
    return 0;
}
