#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t n = 1000;

    for (size_t a = 1; a < 300; a++)
    {
        size_t b = div(n * n - 2 * a * n, 2 * (n - a)).quot;
        size_t c = n - a - b;

        if (a * a + b * b == c * c)
        {
            printf("%ld\n", (size_t)a * b * c);

            return 0;
        }
    }

    return 0;
}
