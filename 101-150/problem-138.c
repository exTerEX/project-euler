#include <stdio.h>
#include <stdint.h>

int main() {
    int64_t sum = 0;
    int64_t a = 17, b = 305;
    sum = a + b;
    for (int i = 3; i <= 12; i++) {
        int64_t c = 18 * b - a;
        sum += c;
        a = b;
        b = c;
    }
    printf("%ld\n", sum);
    return 0;
}
