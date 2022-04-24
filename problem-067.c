#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define FILENAME "problem-067.txt"

int main() {
    FILE* fo;
    int32_t** triangle;

    if ((fo = fopen(FILENAME, "r")) == NULL) {
        printf("ERROR: can't open %s\n", FILENAME);
        return -1;
    }

    triangle = calloc(SIZE, sizeof * triangle);
    for (int32_t i = 0; i < SIZE; ++i) {
        triangle[i] = calloc(i + 1, sizeof * *triangle);
        for (int32_t j = 0; j < i + 1; ++j) { fscanf(fo, "%d", &triangle[i][j]); }
    }

    for (int32_t i = SIZE - 2; i > -1; --i) {
        for (int32_t j = 0; j < i + 1; ++j) {
            triangle[i][j] += (triangle[i + 1][j] > triangle[i + 1][j + 1]) ?
                triangle[i + 1][j] : triangle[i + 1][j + 1];
        }
    }

    printf("%d\n", triangle[0][0]);
    return 0;
}
