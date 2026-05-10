#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 7

bool is_special(int *a);

int main() {
    int base[N] = {20, 31, 38, 39, 40, 42, 45};
    int best[N];
    memcpy(best, base, sizeof(base));
    int best_sum = 0;
    for (int i = 0; i < N; i++) best_sum += best[i];

    int a[N];
    for (int d0 = -3; d0 <= 3; d0++)
    for (int d1 = -3; d1 <= 3; d1++)
    for (int d2 = -3; d2 <= 3; d2++)
    for (int d3 = -3; d3 <= 3; d3++)
    for (int d4 = -3; d4 <= 3; d4++)
    for (int d5 = -3; d5 <= 3; d5++)
    for (int d6 = -3; d6 <= 3; d6++) {
        a[0] = base[0]+d0; a[1] = base[1]+d1; a[2] = base[2]+d2;
        a[3] = base[3]+d3; a[4] = base[4]+d4; a[5] = base[5]+d5;
        a[6] = base[6]+d6;
        bool sorted = true;
        for (int i = 0; i < N-1; i++) if (a[i] >= a[i+1] || a[i] <= 0) { sorted = false; break; }
        if (!sorted) continue;
        int s = 0;
        for (int i = 0; i < N; i++) s += a[i];
        if (s >= best_sum) continue;
        if (is_special(a)) {
            best_sum = s;
            memcpy(best, a, sizeof(a));
        }
    }
    for (int i = 0; i < N; i++) printf("%d", best[i]);
    printf("\n");
    return 0;
}

bool is_special(int *a) {
    int sums[1 << N];
    int count = 0;
    int min_sum[N + 1], max_sum[N + 1];
    for (int i = 0; i <= N; i++) { min_sum[i] = 1 << 30; max_sum[i] = 0; }
    for (int mask = 1; mask < (1 << N); mask++) {
        int s = 0, bits = __builtin_popcount(mask);
        for (int i = 0; i < N; i++) if (mask & (1 << i)) s += a[i];
        for (int j = 0; j < count; j++) if (sums[j] == s) return false;
        sums[count++] = s;
        if (s < min_sum[bits]) min_sum[bits] = s;
        if (s > max_sum[bits]) max_sum[bits] = s;
    }
    for (int k = 1; k < N; k++) {
        if (min_sum[k + 1] <= max_sum[k]) return false;
    }
    return true;
}
