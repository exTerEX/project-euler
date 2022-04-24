#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const double temp = log(10) / log(2);
    int n = 1000, sum = 0;

    uint8_t* digits = calloc((n + temp) / temp, sizeof(uint8_t));

    digits[0] = 1;

    if (!digits)
    {
        perror("Unable to allocate memory!");

        return 1;
    }

    for (int index = 0; index < n; index++)
    {
        int carry = 0;

        for (int jndex = 0; jndex < (n + temp) / temp; jndex++)
        {
            digits[jndex] = (digits[jndex] << 1) + carry;

            if (digits[jndex] > 9)
            {
                carry = 1;
                digits[jndex] -= 10;
            }
            else {
                carry = 0;
            }

            if (index == n - 1) {
                sum += digits[jndex];
            }
        }
    }

    printf("%d\n", sum);

    free(digits);

    return 0;
}
