#include <stdio.h>
#include <stdint.h>

#define MAX 10000000000

int64_t power(int64_t, int64_t);

int main() {
    int64_t a, answer;
    for (a = 1, answer = 0; a < 1000; ++a) {
        answer += power(a, a);
        answer %= MAX;
    }

    printf("%lu\n", answer);
    return 0;
}

int64_t power(int64_t a, int64_t b) {
    int64_t p;
    for (p = 1; b-- > 0; p *= a)
        p %= MAX;

    return p % MAX;
}
