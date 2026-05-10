#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define N 2000

int32_t *g;

int64_t max_subarray(int32_t *arr, int len) {
    int64_t max_sum = arr[0], cur = arr[0];
    for (int i = 1; i < len; i++) {
        cur = (cur + arr[i] > arr[i]) ? cur + arr[i] : arr[i];
        if (cur > max_sum) max_sum = cur;
    }
    return max_sum;
}

int main() {
    g = malloc((int64_t)N * N * sizeof(int32_t));

    uint32_t tbuf[55];
    for (int k = 1; k <= 55; k++) {
        int64_t val = ((int64_t)100003 - (int64_t)200003 * k + (int64_t)300007 * k * k * k) % 1000000;
        if (val < 0) val += 1000000;
        tbuf[k - 1] = (uint32_t)val;
    }

    for (int i = 0; i < N * N; i++) {
        if (i < 55) {
            g[i] = (int32_t)tbuf[i] - 500000;
        } else {
            uint32_t t24 = tbuf[(i - 24 + 110) % 55];
            uint32_t t55 = tbuf[i % 55];
            uint32_t tnew = (t24 + t55) % 1000000;
            tbuf[i % 55] = tnew;
            g[i] = (int32_t)tnew - 500000;
        }
    }

    int64_t best = 0;
    int32_t *tmp = malloc(N * sizeof(int32_t));

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) tmp[c] = g[r * N + c];
        int64_t v = max_subarray(tmp, N);
        if (v > best) best = v;
    }

    for (int c = 0; c < N; c++) {
        for (int r = 0; r < N; r++) tmp[r] = g[r * N + c];
        int64_t v = max_subarray(tmp, N);
        if (v > best) best = v;
    }

    for (int d = -(N - 1); d < N; d++) {
        int len = 0;
        for (int r = 0; r < N; r++) {
            int c = r - d;
            if (c >= 0 && c < N) tmp[len++] = g[r * N + c];
        }
        if (len > 0) {
            int64_t v = max_subarray(tmp, len);
            if (v > best) best = v;
        }
    }

    for (int d = 0; d < 2 * N - 1; d++) {
        int len = 0;
        for (int r = 0; r < N; r++) {
            int c = d - r;
            if (c >= 0 && c < N) tmp[len++] = g[r * N + c];
        }
        if (len > 0) {
            int64_t v = max_subarray(tmp, len);
            if (v > best) best = v;
        }
    }

    printf("%ld\n", best);
    free(g);
    free(tmp);
    return 0;
}
