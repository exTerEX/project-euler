#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int digit_sum(uint64_t n) {
    int s = 0;
    while (n > 0) { s += n % 10; n /= 10; }
    return s;
}

int cmp(const void *a, const void *b) {
    uint64_t x = *(uint64_t *)a, y = *(uint64_t *)b;
    return (x > y) - (x < y);
}

int main() {
    uint64_t results[100];
    int nr = 0;
    for (int base = 2; base <= 100; base++) {
        uint64_t power = base;
        for (int exp = 2; exp <= 50; exp++) {
            if (power > (uint64_t)2.5e17) break;
            power *= base;
            if (power < 10) continue;
            if (digit_sum(power) == base && nr < 100)
                results[nr++] = power;
        }
    }
    qsort(results, nr, sizeof(uint64_t), cmp);
    int unique = 0;
    for (int i = 0; i < nr; i++) {
        if (i == 0 || results[i] != results[i - 1])
            results[unique++] = results[i];
    }
    printf("%lu\n", results[9]);
    return 0;
}
