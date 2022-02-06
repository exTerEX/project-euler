#include <math.h>
#include <stdio.h>
#include <stdbool.h>

bool is_prime(size_t);
size_t sum_of_primes(size_t);

int main()
{
    size_t n = 2000000;

    printf("%ld\n", sum_of_primes(n));

    return 0;
}

bool is_prime(size_t n)
{
    for (size_t index = 2; index < sqrtl(n) + 1; index++)
        if (n % index == 0)
            return false;

    return true;
}

size_t sum_of_primes(size_t n)
{
    size_t sum = 2;

    for (size_t index = 3; index < n; index += 2) {
        if (is_prime(index)) {
            sum += index;
        }
    }

    return sum;
}
