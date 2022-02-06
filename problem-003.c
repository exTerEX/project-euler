#include <stdio.h>

int main()
{
    size_t n = 10, largest = 1, index = 2;

    while (index * index <= n)
    {
        while (n % index == 0)
        {
            largest = index;
            n /= index;
        }

        index += 1;
    }

    if (n > 1) {
        largest = n;
    }

    printf("%ld\n", largest);

    return 0;
}
