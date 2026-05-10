#include <stdint.h>
#include <stdio.h>

static int matches_pattern(uint64_t x) {
    uint64_t sq = x * x;
    static const int want[10] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    for (int i = 0; i < 10; i++) {
        if ((int)(sq % 10ULL) != want[i]) {
            return 0;
        }
        sq /= 100ULL;
    }
    return 1;
}

int main(void) {
    const uint64_t lo = 1010101010ULL;
    const uint64_t hi = 1389026630ULL;

    for (uint64_t x = hi; x >= lo; x -= 10ULL) {
        uint64_t end = x % 100ULL;
        if (end != 30ULL && end != 70ULL) {
            continue;
        }
        if (matches_pattern(x)) {
            printf("%llu\n", (unsigned long long)x);
            return 0;
        }
    }

    return 1;
}
