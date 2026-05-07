#include <stdio.h>
#include <stdint.h>

int main() {
    int64_t x = 1, y = 1;
    for (;;) {
        int64_t nx = 3*x + 4*y;
        int64_t ny = 2*x + 3*y;
        x = nx; y = ny;
        nx = 3*x + 4*y;
        ny = 2*x + 3*y;
        x = nx; y = ny;
        int64_t n = (x + 1) / 2;
        if (n > 1000000000000LL) {
            printf("%ld\n", (y + 1) / 2);
            return 0;
        }
    }
    return 0;
}
