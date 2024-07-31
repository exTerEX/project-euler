#include <stdio.h>
#include <stdint.h>

#define MIN(a, b) (((a)<(b))?(a):(b))
#define SIZE 80
#define FILENAME "problem-081.txt"

int main() {
    FILE* f;
    if ((f = fopen(FILENAME, "r")) == NULL) {
        printf("ERROR: can't open %s\n", FILENAME);
        exit(1);
    }

    int32_t matrix[SIZE][SIZE];

    for (int32_t i = 0; i < SIZE; ++i) {
        for (int32_t j = 0; j < SIZE; ++j) {
            fscanf(f, "%d,", &matrix[i][j]);
        }
    }

    fclose(f);

    for (int32_t i = 1; i < SIZE; ++i) {
        matrix[0][i] += matrix[0][i - 1];
        matrix[i][0] += matrix[i - 1][0];
    }

    for (int32_t i = 1; i < SIZE; ++i) {
        for (int32_t j = 1; j < SIZE; ++j) {
            matrix[i][j] += MIN(matrix[i][j - 1], matrix[i - 1][j]);
        }
    }

    printf("%d\n", matrix[SIZE - 1][SIZE - 1]);

    return 0;
}
