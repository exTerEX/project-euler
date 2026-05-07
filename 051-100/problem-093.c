#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

static double apply_op(double a, double b, int op) {
    switch (op) {
        case 0: return a + b;
        case 1: return a - b;
        case 2: return a * b;
        case 3: return (fabs(b) < 1e-12) ? 1e18 : a / b;
    }
    return 1e18;
}

static void record(uint8_t *found, double v) {
    if (v < 0.5 || v > 1000.5) return;
    long n = (long)(v + 0.5);
    if (n >= 1 && n <= 1000 && fabs(v - (double)n) < 1e-9) found[n] = 1;
}

static void eval4(uint8_t *found, double a, double b, double c, double d) {
    for (int o1 = 0; o1 < 4; o1++)
    for (int o2 = 0; o2 < 4; o2++)
    for (int o3 = 0; o3 < 4; o3++) {
        double ab = apply_op(a, b, o1);
        double bc = apply_op(b, c, o2);
        double cd = apply_op(c, d, o3);
        record(found, apply_op(apply_op(ab, c, o2), d, o3));
        record(found, apply_op(apply_op(a, bc, o1), d, o3));
        record(found, apply_op(ab, cd, o2));
        record(found, apply_op(a, apply_op(bc, d, o3), o1));
        record(found, apply_op(a, apply_op(b, cd, o2), o1));
    }
}

int main() {
    int best_n = 0, best_combo = 0;
    for (int a = 1; a <= 9; a++)
    for (int b = a+1; b <= 9; b++)
    for (int c = b+1; c <= 9; c++)
    for (int d = c+1; d <= 9; d++) {
        uint8_t found[1001];
        memset(found, 0, sizeof(found));
        int p[4] = {a, b, c, d};
        for (int i0 = 0; i0 < 4; i0++)
        for (int i1 = 0; i1 < 4; i1++) { if (i1 == i0) continue;
        for (int i2 = 0; i2 < 4; i2++) { if (i2 == i0 || i2 == i1) continue;
            int i3 = 6 - i0 - i1 - i2;
            eval4(found, p[i0], p[i1], p[i2], p[i3]);
        }}
        int n = 0;
        while (found[n+1]) n++;
        if (n > best_n) {
            best_n = n;
            best_combo = a*1000 + b*100 + c*10 + d;
        }
    }
    printf("%d\n", best_combo);
    return 0;
}
