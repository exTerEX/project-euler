#include <stdio.h>
#include <stdint.h>

#define LIMIT 1000000000LL

int main() {
    int64_t total = 0;

    /* Family 1: b = a-1, perimeter = 3a-1
       Recurrence: a'=7a+4k+2, k'=12a+7k+4, starting (a,k)=(17,30) */
    int64_t a1 = 17, k1 = 30;
    while (3 * a1 - 1 <= LIMIT) {
        total += 3 * a1 - 1;
        int64_t na = 7 * a1 + 4 * k1 + 2;
        int64_t nk = 12 * a1 + 7 * k1 + 4;
        a1 = na; k1 = nk;
    }

    /* Family 2: b = a+1, perimeter = 3a+1
       Recurrence: a'=7a+4k-2, k'=12a+7k-4, starting (a,k)=(5,8) */
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
