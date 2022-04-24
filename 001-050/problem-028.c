#include <stdio.h>
#include <stdint.h>

#define N 1001

int main() {
    uint32_t sum = 1;

    for (uint32_t i = 3; i <= N; i += 2) {
        sum += 2 * (2 * i * i - 3 * i + 3);
    }

    printf("%d\n", sum);

    return 0;
}
