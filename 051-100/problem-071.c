#include <stdio.h>
#include <stdint.h>

int main() {
    uint64_t best_p = 0, best_q = 1;

    for (uint64_t d = 1; d <= 1000000; ++d) {
        uint64_t p = (3 * d - 1) / 7;
        if (p * best_q > best_p * d) {
            best_p = p;
            best_q = d;
        }
    }

    printf("%lu\n", best_p);
    return 0;
}
