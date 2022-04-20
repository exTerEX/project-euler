#include <stdio.h>
#include <stdint.h>
#include <math.h>

int64_t is_pentagonal(int64_t);

int main() {
    int64_t i = 144;
    while (!is_pentagonal(i * (2 * i - 1))) { ++i; }

    printf("%lu\n", i * (2 * i - 1));

    return 0;
}

int64_t is_pentagonal(int64_t n) {
    double value = (sqrt(24 * n + 1) + 1) / 6;
    return value == (int)value;
}
