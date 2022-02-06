#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t x1 = 0, x2 = 1, x3 = 2, sum;

    while (x3 <= 4000000) {
        x3 = x1 + x2;
        sum += x3 * !(x3 % 2);
        x1 = x2;
        x2 = x3;
    }

    printf("%u\n", sum);

    return 0;
}
