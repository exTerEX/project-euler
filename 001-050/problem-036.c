#include <stdio.h>
#include <stdint.h>

#define MAX 1000000

int32_t is_palindrom(int32_t, int32_t);

int main() {
    int32_t answer;

    for (int32_t i = 1, answer = 0; i < MAX; ++i) {
        if (is_palindrom(i, 10) && is_palindrom(i, 2)) {
            answer += i;
        }
    }

    printf("%u\n", answer);

    return 0;
}

int32_t is_palindrom(int32_t n, int32_t base) {
    int32_t m = n, p;
    for (p = 0; n > 0; n /= base) {
        p = base * p + n % base;
    }

    return p == m;
}
