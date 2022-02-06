#include <stdio.h>

int main()
{
    size_t t = 3;

    while (t--)
    {
        size_t N = 10, p = 0, sum = 0;

        for (size_t index = 0; index < N; index++)
        {
            if (index % 3 == 0 || index % 5 == 0)
            {
                sum = sum + index;
            }
        }

        printf("%ld\n", sum);
    }

    return 0;
}
