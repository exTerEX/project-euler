#include <stdio.h>

size_t collatz(size_t);

int main() {
    size_t max_len = 0, nStart = 0;

    for (size_t index = 1; index < 1000000; index++) {
        size_t L = collatz(index);

        if (L > max_len) {
            max_len = L;
            nStart = index;
        }
    }

    printf("%ld\n", nStart);

    return 0;
}

size_t collatz(size_t n) {
    size_t length = 1;

    while (n != 1) {
        if (n & 0x01) {
            n = 3 * n + 1;
        }
        else {
            n >>= 1;
        }
        length++;
    }

    return length;
}
