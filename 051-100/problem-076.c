#include <stdio.h>
#include <stdint.h>

#define MAXINT 100

int main() {
    int32_t ways[MAXINT + 1] = { 0 };
    ways[0] = 1;
    for (int32_t i = 1; i < MAXINT; ++i) {
        for (int32_t j = i; j <= MAXINT; ++j) {
            ways[j] += ways[j - i];
        }
    }

    printf("%d\n", ways[MAXINT]);
    return 0;
}
