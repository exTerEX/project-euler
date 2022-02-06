#include <stdio.h>

int main() {
    size_t s1 = 0, s2 = 0, index;

    for (index = 1; index <= 100; index++) {
        s1 += index * index;
        s2 += index;
    }

    size_t difference = s2 * s2 - s1;

    printf("%ld\n", difference);

    return 0;
}
