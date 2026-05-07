#include <stdio.h>
#include <stdint.h>

int main() {
    /* Pell recurrence: n(n-1) = 2k(k-1), n > 10^12
       Rewrite: 2n^2 - 2n = 4k^2 - 4k
       (2n-1)^2 - 2(2k-1)^2 = -1
       Let x = 2n-1, y = 2k-1: x^2 - 2y^2 = -1
       Fundamental solution: (1,1). Multiply by (3+2*sqrt(2)) to get next.
       (x,y) -> (3x+4y, 2x+3y) */
    int64_t x = 1, y = 1;
    for (;;) {
        int64_t nx = 3*x + 4*y;
        int64_t ny = 2*x + 3*y;
        x = nx; y = ny;
        /* Now x^2 - 2y^2 = 1 (positive), so this gives n = (x+1)/2, k = (y+1)/2 */
        nx = 3*x + 4*y;
        ny = 2*x + 3*y;
        x = nx; y = ny;
        /* Now x^2 - 2y^2 = -1 again */
        int64_t n = (x + 1) / 2;
        if (n > 1000000000000LL) {
            printf("%ld\n", (y + 1) / 2);
            return 0;
        }
    }
    return 0;
}
