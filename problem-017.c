#include <stdio.h>

int main()
{
    size_t s1[] = { 0, 3, 3, 5, 4, 4, 3, 5, 5, 4 };
    size_t s2[] = { 3, 6, 6, 8, 8, 7, 7, 9, 8, 8 };
    size_t s3[] = { 0, 0, 6, 6, 5, 5, 5, 7, 6, 6 };

    size_t sum = 0;

    for (size_t index = 1; index < 10; index++) { sum += s1[index]; }

    for (size_t index = 0; index < 10; index++) { sum += s2[index]; }

    for (size_t index = 20; index < 100; index++) {
        sum += s3[index / 10] + s1[index % 10];
    }

    for (size_t index = 1; index < 10; index++) {
        sum += s1[index] + 7;

        for (size_t jndex = 1; jndex < 10; jndex++) {
            sum += s1[index] + 10 + s1[jndex];
        }

        for (size_t jndex = 0; jndex < 10; jndex++) {
            sum += s1[index] + 10 + s2[jndex];
        }

        for (size_t jndex = 20; jndex < 100; jndex++) {
            sum += s1[index] + 10 + s3[jndex / 10] + s1[jndex % 10];
        }
    }

    sum += s1[1] + 8;

    printf("%ld\n", sum);

    return 0;
}
