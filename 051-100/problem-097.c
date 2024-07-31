#include <stdio.h>
#include <stdint.h>

#define M 10000000000

int main() {
    int64_t answer = 1, power = 7830457, d = 24;

    while (power > d) {
        answer = (answer << d) % M;
        power -= d;
    }

    while (power-- > 0) { answer = (answer << 1) % M; }

    printf("%ld\n", (28433 * answer + 1) % M);

    return 0;
}
