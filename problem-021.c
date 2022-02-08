#include <stdio.h>
#include <stdint.h>

uint32_t divisors_sum(uint32_t);

int main()
{
    uint32_t divisor, sum = 0;

    for (uint32_t i = 2; i < 10000; i++) {
        divisor = divisors_sum(i);

        if (i < divisor && i == divisors_sum(divisor)) {
            sum += i + divisor;
        }
    }

    printf("%d\n", sum);

    return 0;
}

uint32_t divisors_sum(uint32_t n)
{
    uint32_t sum = 1;
    uint32_t k = n;

    for (uint32_t i = 2; i <= k; i++) {
        uint32_t p = 1;

        while (k % i == 0) {
            p *= i;
            k /= i;
        }

        sum *= (p * i - 1) / (i - 1);
    }

    return sum - n;
}
