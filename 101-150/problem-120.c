#include <stdio.h>
#include <stdint.h>

int main() {
    int64_t sum = 0;
    for (int a = 3; a <= 1000; a++) {
        int64_t a2 = (int64_t)a * a;
        int64_t max_r = ((a2 - 1) / (2 * a)) * (2 * a);
        sum += max_r;
    }
    printf("%ld\n", sum);
    return 0;
}
