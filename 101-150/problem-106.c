#include <stdbool.h>
#include <stdio.h>

#define N 12

int count_needed;

bool needs_test(int *b, int *c, int k);
void generate(int n, int k);

int main() {
    count_needed = 0;
    for (int k = 2; k <= N / 2; k++) generate(N, k);
    printf("%d\n", count_needed);
    return 0;
}

bool needs_test(int *b, int *c, int k) {
    bool b_greater = true, c_greater = true;
    for (int i = 0; i < k; i++) {
        if (b[i] <= c[i]) b_greater = false;
        if (c[i] <= b[i]) c_greater = false;
    }
    return !b_greater && !c_greater;
}

void generate(int n, int k) {
    for (int mb = 1; mb < (1 << n); mb++) {
        if (__builtin_popcount(mb) != k) continue;
        for (int mc = mb + 1; mc < (1 << n); mc++) {
            if (__builtin_popcount(mc) != k) continue;
            if (mb & mc) continue;
            int b[N], c[N], bi = 0, ci = 0;
            for (int i = 0; i < n; i++) {
                if (mb & (1 << i)) b[bi++] = i + 1;
                if (mc & (1 << i)) c[ci++] = i + 1;
            }
            if (needs_test(b, c, k)) count_needed++;
        }
    }
}
