#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define MAX 1000
#define max(a,b) (((a)>(b))?(a):(b))

int main() {
    int32_t answer = 0, n_triples[MAX] = { 0 };

    for (int32_t i = 1; i < MAX; ++i) {
        for (int32_t j = i; j <= MAX - i; ++j) {
            for (int32_t k = max(i, j); k <= MAX - i - j; ++k) {
                if (i * i + j * j == k * k) { n_triples[i + j + k]++; }
            }
        }
    }

    for (int32_t i = 0; i < MAX; ++i) {
        if (n_triples[i] > n_triples[answer]) { answer = i; }
    }

    printf("%d\n", answer);
    return 0;
}
