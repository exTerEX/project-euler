#include <stdio.h>

size_t gcd(size_t, size_t);
size_t lcm(size_t, size_t);

int main()
{
    size_t smallest = 1;

    for (size_t i = 1; i <= 20; i++)
    {
        smallest = lcm(smallest, i);
    }

    printf("%ld\n", smallest);

    return 0;
}

size_t gcd(size_t a, size_t b)
{
    size_t r;

    if (a > b)
    {
        size_t t = a;

        a = b;
        b = t;
    }

    while ((r = (a % b)))
    {
        a = b;
        b = r;
    }

    return b;
}

size_t lcm(size_t a, size_t b)
{
    size_t p = (size_t)a * b;

    return p / gcd(a, b);
}
