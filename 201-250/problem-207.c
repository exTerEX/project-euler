#include <stdint.h>
#include <stdio.h>

static int is_power_of_two(uint64_t x) {
    return x != 0 && (x & (x - 1ULL)) == 0ULL;
}

int main(void) {
    const uint64_t numerator = 1;
    const uint64_t denominator = 12345;

    uint64_t perfect = 1;
    uint64_t total = 1;
    uint64_t x = 3;

    while (perfect * denominator > total * numerator) {
        if (is_power_of_two(x)) {
            perfect++;
        }
        total++;
        x++;
    }

    uint64_t m = x * (x - 1ULL);
    printf("%llu\n", (unsigned long long)m);
    return 0;
}
