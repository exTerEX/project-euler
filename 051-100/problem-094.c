#include <stdio.h>
#include <stdint.h>

#define LIMIT 1000000000LL

int main() {
    int64_t total = 0;

    int64_t a1 = 17, k1 = 30;
    while (3 * a1 - 1 <= LIMIT) {
        total += 3 * a1 - 1;
        int64_t na = 7 * a1 + 4 * k1 + 2;
        int64_t nk = 12 * a1 + 7 * k1 + 4;
        a1 = na; k1 = nk;
    }

    int64_t a2 = 5, k2 = 8;
    while (3 * a2 + 1 <= LIMIT) {
        total += 3 * a2 + 1;
        int64_t na = 7 * a2 + 4 * k2 - 2;
        int64_t nk = 12 * a2 + 7 * k2 - 4;
        a2 = na; k2 = nk;
    }

    printf("%ld\n", total);
    return 0;
}
