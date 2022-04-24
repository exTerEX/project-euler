#include <stdio.h>

size_t routes(size_t);

int main() {
    printf("%ld\n", routes(20));

    return 0;
}

size_t routes(size_t n) {
    size_t route = 1;

    for (size_t index = 0; index < n; index++) {
        route *= (n << 1) - index;
        route /= index + 1;
    }

    return route;
}
