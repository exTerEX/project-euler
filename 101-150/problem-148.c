#include <stdio.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000000LL;

    int digits[15];
    int nd = 0;
    int64_t tmp = N;
    while (tmp > 0) { digits[nd++] = tmp % 7; tmp /= 7; }

    int64_t ans = 0;
    int64_t prefix_product = 1;

    for (int i = nd - 1; i >= 0; i--) {
        int d = digits[i];
        int64_t free_contrib = 1;
        for (int k = 0; k < i; k++) free_contrib *= 28;
        int64_t partial = (int64_t)d * (d + 1) / 2 * free_contrib;
        ans += prefix_product * partial;
        prefix_product *= (d + 1);
    }

    printf("%ld\n", ans);
    return 0;
}
