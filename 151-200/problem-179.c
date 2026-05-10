#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 10000000

int main(void) {
    uint16_t *divisors = (uint16_t *)calloc(LIMIT + 1, sizeof(uint16_t));
    if (divisors == NULL) {
        return 1;
    }

    for (int i = 1; i <= LIMIT; i++) {
        for (int j = i; j <= LIMIT; j += i) {
            divisors[j]++;
        }
    }

    int count = 0;
    for (int n = 2; n < LIMIT; n++) {
        if (divisors[n] == divisors[n + 1]) {
            count++;
        }
    }

    printf("%d\n", count);
    free(divisors);
    return 0;
}
