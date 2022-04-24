#include <math.h>
#include <stdio.h>

size_t count_divisors(size_t);

int main() {
    size_t index = 1, divisors, triangle_number = 1;

    while (1) {
        index++;
        triangle_number += index;
        divisors = count_divisors(triangle_number);

        if (divisors > 500) {
            break;
        }
    }

    printf("%ld\n", triangle_number);

    return 0;
}

size_t count_divisors(size_t n) {
    size_t divisors = 0;

    for (size_t index = 1; index < sqrtl(n) + 1; index++) {
        if (n % index == 0) {
            divisors += 2;
        }
        else if (index * index == n) {
            divisors += 1;
        }
    }

    return divisors;
}
