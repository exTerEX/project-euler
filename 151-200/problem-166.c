#include <stdint.h>
#include <stdio.h>

static int grid[16];
static int64_t total_count = 0;

static int min_int(int a, int b) {
    return (a < b) ? a : b;
}

static void dfs(int sum, int depth) {
    if (depth == 15) {
        total_count++;
        return;
    }

    if (depth < 3) {
        for (int d = 0; d <= 9; d++) {
            grid[depth] = d;
            dfs(sum, depth + 1);
        }
        return;
    }

    if (depth == 3) {
        for (int d = 0; d <= 9; d++) {
            grid[3] = d;
            dfs(grid[0] + grid[1] + grid[2] + grid[3], 4);
        }
        return;
    }

    if (depth == 4) {
        for (int d = 0; d <= min_int(sum, 9); d++) {
            grid[4] = d;
            dfs(sum, 5);
        }
        return;
    }

    if (depth == 5) {
        for (int d = 0; d <= min_int(sum - grid[4], 9); d++) {
            grid[5] = d;
            dfs(sum, 6);
        }
        return;
    }

    if (depth == 6) {
        for (int d = 0; d <= min_int(sum - grid[4] - grid[5], 9); d++) {
            int h = sum - grid[4] - grid[5] - d;
            if (h >= 0 && h <= 9) {
                grid[6] = d;
                grid[7] = h;
                dfs(sum, 8);
            }
        }
        return;
    }

    if (depth == 8) {
        for (int i = 0; i <= min_int(sum - grid[0] - grid[4], 9); i++) {
            int m = sum - grid[0] - grid[4] - i;
            if (m < 0 || m > 9) {
                continue;
            }

            int j = sum - grid[3] - grid[6] - m;
            if (j < 0 || j > 9) {
                continue;
            }

            int n = sum - grid[1] - grid[5] - j;
            if (n < 0 || n > 9) {
                continue;
            }

            int twice_k = sum - grid[0] - grid[5] - i - j + grid[3] + grid[7];
            if (twice_k < 0 || twice_k > 18 || (twice_k & 1) != 0) {
                continue;
            }

            int k = twice_k / 2;
            int o = sum - grid[2] - grid[6] - k;
            if (o < 0 || o > 9) {
                continue;
            }

            int l = sum - i - j - k;
            if (l < 0 || l > 9) {
                continue;
            }

            int p = sum - grid[0] - grid[5] - k;
            if (p < 0 || p > 9) {
                continue;
            }

            if (m + n + o + p != sum) {
                continue;
            }

            grid[8] = i;
            grid[9] = j;
            grid[10] = k;
            grid[11] = l;
            grid[12] = m;
            grid[13] = n;
            grid[14] = o;
            grid[15] = p;
            dfs(sum, 15);
        }
    }
}

int main(void) {
    total_count = 0;
    dfs(0, 0);
    printf("%lld\n", (long long)total_count);
    return 0;
}
