#include <stdio.h>
#include <stdint.h>

static int has_digit(int cube, int d) {
    if (d == 6 || d == 9) return ((cube >> 6) & 1) || ((cube >> 9) & 1);
    return (cube >> d) & 1;
}

static int can_show(int c1, int c2, int a, int b) {
    return (has_digit(c1, a) && has_digit(c2, b)) ||
           (has_digit(c1, b) && has_digit(c2, a));
}

int main() {
    int cubes[210], nc = 0;
    for (int mask = 0; mask < 1024; ++mask)
        if (__builtin_popcount(mask) == 6) cubes[nc++] = mask;

    int sq[9][2] = {{0,1},{0,4},{0,9},{1,6},{2,5},{3,6},{4,9},{6,4},{8,1}};
    int count = 0;
    for (int i = 0; i < nc; ++i) {
        for (int j = i; j < nc; ++j) {
            int ok = 1;
            for (int k = 0; k < 9 && ok; ++k)
                ok = can_show(cubes[i], cubes[j], sq[k][0], sq[k][1]);
            if (ok) ++count;
        }
    }
    printf("%d\n", count);
    return 0;
}
