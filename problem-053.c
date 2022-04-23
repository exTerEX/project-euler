#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define N 100
#define MAX 1000000

int main() {
    int32_t answer = 0, binomial[N + 1][N + 1] = { 0 };

    binomial[1][0] = binomial[1][1] = 1;
    for (int32_t i = 2; i <= N; ++i) {
        binomial[i][0] = 1;
        for (int32_t j = 1; j < i; ++j) {
            binomial[i][j] = binomial[i - 1][j] + binomial[i - 1][j - 1];

            if (binomial[i][j] > MAX) {
                answer += i - j - j + 1;
                break;
            }
        }
        binomial[i][i] = 1;
    }

    printf("%d\n", answer);
    return 0;
}
