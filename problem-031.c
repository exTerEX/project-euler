#include <stdio.h>
#include <stdint.h>

int main() {
    int32_t coins[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };
    int64_t ways[200 + 1] = { 0 };

    ways[0] = 1;
    for (int32_t i = 0; i < 8; ++i) {
        for (int32_t j = coins[i]; j <= 200; ++j) {
            ways[j] += ways[j - coins[i]];
        }
    }

    printf("%lu\n", ways[200]);
    return 0;
}

