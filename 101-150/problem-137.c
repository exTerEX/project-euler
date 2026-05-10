#include <stdio.h>
#include <stdint.h>

int main() {
    int64_t a = 1, b = 1;
    for (int i = 2; i < 31; i++) {
        int64_t c = a + b;
        a = b;
        b = c;
    }
    printf("%ld\n", a * b);
    return 0;
}
