#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define M 1000000
#define EXP 5

int main() {
    uint8_t buf[16];
    uint32_t product = 0;

    for (uint32_t i = 10; i < M; i++) {
        uint32_t sum = 0;

        snprintf(buf, sizeof(buf), "%d", i);

        for (uint32_t j = 0; buf[j]; j++) {
            sum += pow(buf[j] - '0', EXP);
        }

        if (i == sum) { product += i; }
    }

    printf("%d\n", product);

    return 0;
}
