#include <stdio.h>
#include <stdint.h>

int main() {
    uint64_t n = 600851475143, prime = 1, index = 2;

    while (index * index <= n) {
        while (n % index == 0) {
            prime = index;
            n /= index;
        }

        index += 1;
    }

    if (n > 1) {
        prime = n;
    }

    printf("%ld\n", prime);

    return 0;
}
