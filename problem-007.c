#include <stdio.h>
#include <stdlib.h>

int main()
{
    const size_t n = 1000000;
    size_t count = 0;

    char* sieve = (char*)calloc(n, sizeof(char));

    for (size_t prime = 2; prime < n; prime++)
    {
        if (!sieve[prime])
        {
            count++;

            if (count == 10001)
            {
                printf("%ld\n", prime);
                break;
            }

            for (size_t jndex = prime * 2; jndex < n; jndex += prime)
            {
                sieve[jndex] = 1;
            }
        }
    }

    free(sieve);

    return 0;
}
