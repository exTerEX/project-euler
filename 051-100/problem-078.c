#include <stdio.h>
#include <stdint.h>

#define LIM 60000
#define MOD 1000000

int main() {
    int32_t pentagonal[LIM] = { 0 };

    for (int32_t i = 1, j = 0; i < LIM; ++i, ++j) {
        pentagonal[j] = i * (3 * i - 1) / 2;
        if (pentagonal[j] > LIM) { break; }

        pentagonal[++j] = i * (3 * i + 1) / 2;
        if (pentagonal[j] > LIM) { break; }
    }

    int32_t partitions[LIM] = { 0 };
    partitions[0] = 1;

    for (int32_t i = 1; i < LIM; ++i) {
        for (int32_t j = 0; j < LIM; ++j) {
            if ((i - pentagonal[j]) < 0) { break; }
            if ((j & 2) == 0) { partitions[i] += partitions[i - pentagonal[j]]; }
            else { partitions[i] -= partitions[i - pentagonal[j]]; }
        }

        partitions[i] %= MOD;
    }

    for (int32_t i = 0; i < LIM; ++i) {
        if (partitions[i] == 0) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}
