#include <stdio.h>
#include <stdbool.h>

bool is_palindromic(size_t);

int main() {
    size_t largest = 0;

    for (size_t index = 100; index <= 999; index++) {
        for (size_t jndex = 100; jndex <= 999; jndex++) {
            size_t p = index * jndex;

            if (is_palindromic(p) && p > largest) {
                largest = p;
            }
        }
    }

    printf("%ld\n", largest);

    return 0;
}

bool is_palindromic(size_t n) {
    size_t reversed = 0, t = n;

    while (t > 0) {
        reversed = 10 * reversed + (t % 10);
        t /= 10;
    }

    return reversed == n;
}
